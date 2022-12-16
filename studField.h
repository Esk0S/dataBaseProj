#ifndef DATABASEPROJ_STUDFIELD_H
#define DATABASEPROJ_STUDFIELD_H
#include <utility>
#include "sqlite3.h"
#include "abstractField.h"

class studField : public abstractField {
protected:
    string name;

public:
    studField(int id, string name) : abstractField(id)
    {
        this->name = std::move(name);
    }
    explicit studField(int id) : abstractField(id)
    {
        this->name = "Undefined";
    }

    bool input(sqlite3 *db) {
        char sql_query[] = "INSERT INTO Stud_info (stud_name) values ('?');";
        int rc;
        sqlite3_stmt *stmt;
        rc = sqlite3_prepare_v2(db, sql_query, -1, &stmt, NULL);

        if(rc != SQLITE_OK)
        {
            cerr << "Cannot open prepare statement: " << sqlite3_errmsg(db) << endl;
            sqlite3_close(db);
            return false;
        }



    }
};


#endif
