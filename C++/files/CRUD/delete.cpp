#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;

int main() {
    // Delete the file
    if (remove("C:\\Users\\veraf\\Desktop\\VsCode_file\\C++\\files\\newfile.py") == 0) { //full way to the file
        cout << "File deleted successfully.\n";
    } else {
        cout << "Error deleting the file.\n";
    }

    return 0;
}