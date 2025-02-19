#include <iostream>
#include <fstream>
#include <filesystem>
#include <sqlite3.h>
#include <iomanip>

using namespace std;

void printUsersTable(const std::string& dbPath) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    const char* query = "SELECT ID, email FROM users"; // Modified query to select specific columns

    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error preparing query: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    // Print column headers
    int cols = sqlite3_column_count(stmt);
    std::cout << "--- Users Table (ID, email) ---" << std::endl;

    for (int i = 0; i < cols; i++) {
        std::cout << std::setw(15) << std::left << sqlite3_column_name(stmt, i);
    }
    std::cout << std::endl;
    std::cout << std::string(cols * 15, '-') << std::endl;

    // Print rows
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        for (int i = 0; i < cols; i++) {
            const char* val = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
            std::cout << std::setw(15) << std::left << (val ? val : "NULL");
        }
        std::cout << std::endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}


int main() {
    const std::string subfolder = "C:\\Users\\veraf\\Desktop\\cloudSim\\C++\\data\\log_files";
    const std::string clonedDb = subfolder + "\\cloudSim_clone.db";

    printUsersTable(clonedDb);
}