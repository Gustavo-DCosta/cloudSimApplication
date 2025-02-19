#include <iostream>
#include <filesystem>
#include <cstdio>
using namespace std;

int main() {
    string choice;
    string oldfile;

    cout << "To change the name of the file, would you like to insert the new one? Y/n ?: ";
    cin >> choice;
    cout << "What is the old file you would like to rename? Please insert with : ";
    cin >> oldfile;

    if (choice == "Y") {
        string new_file_name;
        cout << "What would be the name of the new file?" << endl;
        cin >> new_file_name;

        // Attempt to rename the file
        if (rename(oldfile.c_str(), new_file_name.c_str()) == 0) {
            cout << "The file was successfully renamed to: " << new_file_name << endl;
        } else {
            cout << "Error renaming file. Please check the file name and try again." << endl;
        }
    } else {
        cout << "Operation canceled." << endl;
    }

    return 0;
}
