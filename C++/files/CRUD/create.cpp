#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ofstream newfile("newfile.cpp");  // Open the file

    if (newfile.is_open()) {  // Check if the file was successfully opened
        cout << "The file was successfully created" << endl;
    } else {
        cout << "File wasn't successfully created" << endl;
    }

    newfile.close();  // Close the file
    return 0;
}
