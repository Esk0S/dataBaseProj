#ifndef DATABASEPROJ_COURSEFIELD_H
#define DATABASEPROJ_COURSEFIELD_H
#include <utility>
#include "sqlite3.h"
#include "abstractField.h"

class courseField : abstractField {
protected:
    int course;

public:
    courseField(int id, int course) : abstractField(id), course(course)
    {
    }

    bool input(sqlite3 *db) override;
};


#endif