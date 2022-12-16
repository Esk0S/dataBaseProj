#include <iostream>
#include <cstring>
#include "sqlite3.h"
#include "idField.h"
#include "abstractField.h"

using namespace std;

bool createTable(sqlite3 *db) {
    char sql_query[] = "CREATE TABLE Stud_info (\n"
                       "    id        INTEGER PRIMARY KEY,\n"
                       "    stud_name TEXT,\n"
                       "    course    INTEGER,\n"
                       "    [group]   TEXT,\n"
                       "    faculty   TEXT\n"
                       ");";
    int rc;
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql_query, -1, &stmt, NULL);

    if(rc != SQLITE_OK)
    {
        if (strcmp(sqlite3_errmsg(db), "table Stud_info already exists") == 0) {
            cerr << "Cannot open prepare statement: " << sqlite3_errmsg(db) << endl;
            return false;
        }
        cerr << "Cannot open prepare statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return false;
    }
    int step = sqlite3_step(stmt);

    while(step == SQLITE_ROW)
    {
        step = sqlite3_step(stmt);
    }
    return true;
}


int main() {
    sqlite3 *db;
    int rc = sqlite3_open("database.db", &db);
    if(rc != SQLITE_OK) {
        cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return 1;
    }

    createTable(db);

    idField field_id(7);
    field_id.input(db);

    abstractField::output(db, 1);

    return 0;
}
