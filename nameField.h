#ifndef DATABASEPROJ_NAMEFIELD_H
#define DATABASEPROJ_NAMEFIELD_H
#include <utility>
#include "sqlite3.h"
#include "abstractField.h"

class nameField : abstractField{
protected:
    char *stud_name;

public:
    nameField(int id, char *stud_name) : abstractField(id), stud_name(stud_name)
    {
    }

    bool input(sqlite3 *db) override;

};


#endif