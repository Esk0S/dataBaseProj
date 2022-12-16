#include "idField.h"

bool idField::input(sqlite3 *db) {
    char sql_query[] = "INSERT INTO Stud_info (id) values (?);";
    int rc;
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql_query, -1, &stmt, NULL);

    if(rc != SQLITE_OK)
    {
        cerr << "Cannot open prepare statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return false;
    }

    sqlite3_clear_bindings(stmt);
    sqlite3_reset(stmt);
    sqlite3_bind_int(stmt, 1, id);

    int step = sqlite3_step(stmt);
    if (step == SQLITE_CONSTRAINT) {
        cout << "This ID already exist" << endl;
    }
    if (step == SQLITE_DONE) {
        cout << "successfully ID insert" << endl;
    }

    sqlite3_finalize(stmt);

    return true;
}
