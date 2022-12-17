#ifndef DATABASEPROJ_FACULTYFIELD_H
#define DATABASEPROJ_FACULTYFIELD_H
#include <utility>
#include "sqlite3.h"
#include "abstractField.h"

class facultyField : abstractField {
protected:
    char *faculty;

public:
    facultyField(int id, char *faculty) : abstractField(id), faculty(faculty)
    {
    }

    bool input(sqlite3 *db) override;
};


#endif