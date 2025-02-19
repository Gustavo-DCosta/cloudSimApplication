#include <iostream>
#include <fstream> 
#include <sqlite3.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
#include <sstream>
#include <random>
#include <openssl/sha.h>

using namespace std;


// Rotate right (ROR) operation
unsigned long long rotateRight(unsigned long long value, int bits) {
    return (value >> bits) | (value << (64 - bits));
}

// Secure Random Salt Generator
string generateSalt(size_t length) {
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> dist(0, 255);
    
    string salt;
    for (size_t i = 0; i < length; ++i) {
        salt += static_cast<char>(dist(generator));
    }
    return salt;
}

// Example SHA-512 Function (Simplified for Illustration)
string sha512(const string &input) {
    // Initialize hash values, constants, etc.
    unsigned long long H[8] = {
        0x6a09e667f3bcc908, 0xbb67ae8584caa73b, 
        0x3c6ef372fe94f82b, 0xa54ff53a5f1d36f1, 
        0x510e527fade682d1, 0x9b05688c2b3e6c1f, 
        0x1f83d9abfb41bd6b, 0x5be0cd19137e2179
    };

    // Pre-processing and chunking omitted for brevity
    // Main compression loop should go here

    // Produce final hash value
    ostringstream result;
    for (int i = 0; i < 8; ++i) {
        result << hex << setw(16) << setfill('0') << H[i];
    }
    return result.str();
}

// Function to count letters in a string
int countLetters(const string& str) {
    int count = 0;
    for (char ch : str) {
        if (isalpha(ch)) { // Check if character is a letter
            count++;
        }
    }
    return count;
}

// Callback function to print the result of the SELECT query
static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << endl;
    }
    cout << "--------------------------" << endl;
    return 0;
}

// Function to handle user registration
void registerUser(sqlite3* db) {
    char* errMessage = 0;
    srand(time(0)); // seed the random number generator

    const char* alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int random_index = rand() % 52; // 52 is the length of the alphabet string
    char random_letter = alphabet[random_index];

    string email, password;
    int phone_number;
    char ID = random_letter; // Assigns a random letter as the ID

    // Take user input
    cout << "This is your ID: " << ID << endl;
    cout << "Enter your e-mail please: ";
    cin >> email;
    cout << "Enter your password: ";
    cin >> password;
    cout << "Enter your phone number please: ";
    cin >> phone_number;

    // Loop until the user provides a password with more than 3 letters
    while (true) {
        cout << "Enter your password: ";
        getline(cin, password);

        // Count the number of letters in the password
        int letterCount = countLetters(password);

        if (letterCount > 3) {
            break; // Exit the loop if the password is valid
        } else {
            cout << "Error: Password must contain more than 3 letters.\n";
        }
    }

    // Step 1: Generate a salt
    string salt = generateSalt(16); // 16 bytes of random salt

    // Step 2: Combine the data and salt
    string combined = salt + password;

    // Step 3: Hash the combined data
    string hash = sha512(combined);
    // print salt
    cout << "Salt: " << salt << endl;
    // Output: Display and hash
    cout << "Hash: " << hash << endl;

    // Create SQL insert statement
    string sql = "INSERT INTO users (ID, email, password, phone_number, salt) VALUES ('" + 
             string(1, ID) + "', '" + email + "', '" + hash + "', " + 
             to_string(phone_number) + ", '" + salt + "');";


    // Execute the SQL statement
    int exit = sqlite3_exec(db, sql.c_str(), 0, 0, &errMessage);
    if (exit != SQLITE_OK) {
        cerr << "SQL error: " << errMessage << endl;
        sqlite3_free(errMessage);
    } else {
        cout << "Record inserted successfully!" << endl;
    }
}

// Function to handle user login
bool loginUser(sqlite3* db) {
    string email, password;
    cout << "\nLogin" << endl;
    cout << "Enter your email: ";
    cin >> email;
    cout << "Enter your password: ";
    cin >> password;

    // Prepare the SQL query with parameterized inputs
    string sql = "SELECT salt, password FROM users WHERE email = ?;";
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    // Bind the email parameter
    sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_STATIC);

    // Execute the query
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        // Retrieve the salt and hashed password from the database
        string dbSalt = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        string dbPassword = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));

        // Combine the retrieved salt with the entered password and hash it
        string combined = dbSalt + password;
        string hashedInput = sha512(combined);

        if (hashedInput == dbPassword) {
            cout << "Login successful!" << endl;
            sqlite3_finalize(stmt);
            return true;
        } else {
            cout << "Incorrect password!" << endl;
        }
    } else {
        cout << "No user found with this email!" << endl;
    }

    // Finalize the statement and return false if login fails
    sqlite3_finalize(stmt);
    return false;
}

int main() {
    sqlite3* db;
    char* errMessage = 0;   
    int exit = sqlite3_open("cloudSim.db", &db);
    if (exit) {
        cerr << "Oh uh, something went wrong... " << sqlite3_errmsg(db) << endl;
        return exit;
    } else {
        cout << "Opened database successfully!!" << endl;
    }

    // Create the 'users' table if it does not exist
    string create_table_sql = 
        "CREATE TABLE IF NOT EXISTS users ("
        "ID CHAR(1) PRIMARY KEY, "
        "email TEXT NOT NULL, "
        "password TEXT NOT NULL, "
        "phone_number INT NOT NULL, "
        "salt TEXT NOT NULL"
    ");";
    
    exit = sqlite3_exec(db, create_table_sql.c_str(), 0, 0, &errMessage);
    if (exit != SQLITE_OK) {
        cerr << "Table creation error: " << errMessage << endl;
        sqlite3_free(errMessage);
    } else {
        cout << "Table ensured to exist or created successfully!" << endl;
    }

    int choice;
    do {
        cout << "\n1. Register\n2. Login\n3. View Users\n4. Exit\nChoose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser(db);
                break;
            case 2:
                if (loginUser(db)) {
                    cout << "Welcome to the system!" << endl;
                }
                break;
            case 3: {
                string sql = "SELECT * FROM users;";
                cout << "\n--- User Table ---\n";
                exit = sqlite3_exec(db, sql.c_str(), callback, 0, &errMessage);
                if (exit != SQLITE_OK) {
                    cerr << "SQL error: " << errMessage << endl;
                    sqlite3_free(errMessage);
                }
                break;
            }
            case 4:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid option. Try again!" << endl;
        }
    } while (choice != 4);

    sqlite3_close(db);
    return 0;
}
