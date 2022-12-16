#include "abstractField.h"

bool abstractField::output(sqlite3 *db, int _id)
{
    char sql_query[] = "SELECT id, "
                       "stud_name, "
                       "course, "
                       "\"group\", "
                       "faculty "
                       "FROM Stud_info "
                       "WHERE id = ?; ";
    int rc;
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql_query, -1, &stmt, NULL);

    if(rc != SQLITE_OK)
    {
        cerr << "Cannot open prepare statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return false;
    }

    auto *result = new Result;
    sqlite3_clear_bindings(stmt);
    sqlite3_reset(stmt);
    sqlite3_bind_int(stmt, 1, _id);

    int step = sqlite3_step(stmt);
    while(step == SQLITE_ROW)
    {
        step = sqlite3_step(stmt);
    }

    int c = sqlite3_column_int(stmt, 0);
    (*result).id = c;

    char *b = (char*)sqlite3_column_text(stmt, 1);
    size_t size = sizeof(char*) * strlen(b);
    (*result).stud_name = new char[size];
    memcpy((*result).stud_name, b, size);

    c = sqlite3_column_int(stmt, 2);
    (*result).course = c;

    b = (char*)sqlite3_column_text(stmt, 3);
    size = sizeof(char*) * strlen(b);
    (*result).group = new char[size];
    memcpy((*result).group, b, size);

    b = (char*)sqlite3_column_text(stmt, 4);
    size = sizeof(char*) * strlen(b);
    (*result).faculty = new char[size];
    memcpy((*result).faculty, b, size);

    cout << result->id << '\t' << result->stud_name << '\t' << result->course << '\t'
    << result->group << '\t' << result->faculty << endl;

    return true;
}