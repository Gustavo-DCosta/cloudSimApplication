#include <iostream>
#include <vector>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

using namespace std;

int main() {

    string password;
    cout << "Insert your password: ";
    cin >> password;
    cout << "the password lenght is: " << password.size() << endl;

    if (password.size() <= 3) {
        cout << "The password is to small please chose another one: " << endl;
    }
    else {
        cout << "the password size seems good you can proceed..." << endl;
    }
    
    // Initialize the seed for rand()
    srand(time(0)); // Use the current time for randomness

    // Vector to store random characters
    vector<char> randomChars;

    // Generate 24 random letters (upper and lowercase)
    for (int i = 0; i < 24; ++i) {
        if (rand() % 2 == 0) {
            // Random uppercase letter (A-Z)
            char randomUpper = 'A' + rand() % 26;
            randomChars.push_back(randomUpper);
        } else {
            // Random lowercase letter (a-z)
            char randomLower = 'a' + rand() % 26;
            randomChars.push_back(randomLower);
        }
    }

    // Vector to store random integers
    vector<int> randomIntegers;

    // Generate 10 random integers (0-9)
    for (int i = 0; i < 10; ++i) {
        int randomNum = rand() % 10; // Random number between 0 and 9
        randomIntegers.push_back(randomNum);
    }
    
    // Combine randomChars and randomIntegers into a single hashedpassword string
    string hashedpassword;

    for (char c : randomChars) {
        hashedpassword += c;
    }

    for (int num : randomIntegers) {
        hashedpassword += to_string(num); // Convert int to string and append
    }

    cout << "Hashed password: " << hashedpassword << endl;

    return 0;
}
