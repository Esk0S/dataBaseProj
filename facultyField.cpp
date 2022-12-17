#include "facultyField.h"

bool facultyField::input(sqlite3 *db) {
    char sql_query[200] = "UPDATE Stud_info SET faculty = '";
    strcat(sql_query, faculty);
    strcat(sql_query, "' WHERE id = ?; ");

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
//    if (step == SQLITE_DONE) {
//        cout << "successful faculty insertion" << endl;
//    }

    sqlite3_finalize(stmt);

    return true;
}