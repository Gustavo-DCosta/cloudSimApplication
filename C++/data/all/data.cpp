#include <iostream>
#include <fstream> 
#include <sqlite3.h>
#include <cstdlib>
#include <ctime>
using namespace std;

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

    // Create SQL insert statement
    string sql = "INSERT INTO users (ID, email, password, phone_number) VALUES ('" + 
                 string(1, ID) + "', '" + email + "', '" + password + "', " + 
                 to_string(phone_number) + ");";

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

    // Prepare the SQL query
    string sql = "SELECT password FROM users WHERE email = '" + email + "';";
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    // Execute the query
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        string dbPassword = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        if (dbPassword == password) {
            cout << "Login successful!" << endl;
            sqlite3_finalize(stmt);
            return true;
        } else {
            cout << "Incorrect password!" << endl;
        }
    } else {
        cout << "No user found with this email!" << endl;
    }
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
        "phone_number INT NOT NULL);";
    
    exit = sqlite3_exec(db, create_table_sql.c_str(), 0, 0, &errMessage);
    if (exit != SQLITE_OK) {
        cerr << "Table creation error: " << errMessage << endl;
        sqlite3_free(errMessage);
    } else {
        cout << "Table ensured to exist or created successfully!" << endl;
    }

    int choice;
    do {
        cout << "\n1. Register\n2. Login\n3. Exit\nChoose an option: ";
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
            case 3:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid option. Try again!" << endl;
        }
    } while (choice != 3);

    sqlite3_close(db);
    return 0;
}
