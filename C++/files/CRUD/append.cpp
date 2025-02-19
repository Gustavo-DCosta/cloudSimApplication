#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    string filename;
    string new_text;

    cout << "Enter the name of the file to update: ";
    cin >> filename;

    cout << "Enter the text you want to add: ";
    cin.ignore();  // Ignore any leftover newline from previous input
    getline(cin, new_text);

    // Open file in append mode
    ofstream file(filename, ios::app);
    if (file.is_open()) {
        file << new_text << endl;  // Add the new text to the end of the file
        cout << "Text added successfully." << endl;
    } else {
        cout << "Error: Could not open the file." << endl;
    }

    file.close();
    return 0;
}
