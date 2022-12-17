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

    sqlite3_clear_bindings(stmt);
    sqlite3_reset(stmt);
    sqlite3_bind_int(stmt, 1, _id);

    int step = sqlite3_step(stmt);
    while(step == SQLITE_ROW)
    {
        step = sqlite3_step(stmt);
    }
    sqlite3_reset(stmt);
    step = sqlite3_step(stmt);

    int c = sqlite3_column_int(stmt, 0);
    if (c != 0) {
        auto *result = new Result;
        (*result).id = c;

        char *b;
        size_t size;
        if (sqlite3_column_type(stmt, 1) != SQLITE_NULL) {
            b = (char *) sqlite3_column_text(stmt, 1);
            size = sizeof(char *) * strlen(b);
            (*result).stud_name = new char[size];
            memcpy((*result).stud_name, b, size);
        } else {
            (*result).stud_name = new char[5];
            memcpy((*result).stud_name, "NULL", 5);
        }

        c = sqlite3_column_int(stmt, 2);
        (*result).course = c;

        if (sqlite3_column_type(stmt, 3) != SQLITE_NULL) {
            b = (char *) sqlite3_column_text(stmt, 3);
            size = sizeof(char *) * strlen(b);
            (*result).group = new char[size];
            memcpy((*result).group, b, size);
        } else {
            (*result).group = new char[5];
            memcpy((*result).group, "NULL", 5);
        }

        if (sqlite3_column_type(stmt, 4) != SQLITE_NULL) {
            b = (char *) sqlite3_column_text(stmt, 4);
            size = sizeof(char *) * strlen(b);
            (*result).faculty = new char[size];
            memcpy((*result).faculty, b, size);
        } else {
            (*result).faculty = new char[5];
            memcpy((*result).faculty, "NULL", 5);
        }

        cout << result->id << '\t' << result->stud_name << '\t' << result->course << '\t'
             << result->group << '\t' << result->faculty << endl;

        delete[] result->faculty;
        delete[] result->group;
        delete[] result->stud_name;
        delete result;
    } else {
        cerr << "ID " << _id << " does not exist in table" << endl;
    }

    return true;
}

bool abstractField::delete_str(sqlite3 *db, int _id)
{
    char sql_query[] = "DELETE FROM Stud_info WHERE id = ?";

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
    sqlite3_bind_int(stmt, 1, _id);

    int step = sqlite3_step(stmt);
    while(step == SQLITE_ROW)
    {
        step = sqlite3_step(stmt);
    }
    return true;
}

int callback(void *NotUsed, int argc, char **argv,
             char **azColName) {
    NotUsed = NULL;
    for (int i = 0; i < argc; i++) {
        if ( argv[i] == NULL ) {
            printf("NULL\t", azColName[i]);
        } else {
            printf("%s\t", argv[i]);
        }
    }
    cout << '\n';
    return 0;
}

bool abstractField::output_table(sqlite3 *db)
{
    char sql_query[] = "SELECT * FROM Stud_info";
    char *err_msg = NULL;
    int rc = sqlite3_exec(db, sql_query, callback, 0, &err_msg);

    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return false;
    }



    return true;
}