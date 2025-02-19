#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

string simpleHash(const string &input) {
    string hash = "";
    int salt = 31; 
    srand(static_cast<unsigned int>(time(0)));

    for (size_t i = 0; i < input.length(); i++) {
        // Add the ASCII value of each character with a random number
        char modifiedChar = input[i] + (rand() % 10) + salt;
        
        modifiedChar ^= salt;
        
        hash += to_string(modifiedChar);
    }
    
    return hash;
}

int main() {
    string password;
    cout << "Please enter a password: ";
    cin >> password;

    string hashedPassword = simpleHash(password);
    cout << "Hashed password: " << hashedPassword << endl;

    return 0;
}
