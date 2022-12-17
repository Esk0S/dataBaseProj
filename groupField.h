#ifndef DATABASEPROJ_GROUPFIELD_H
#define DATABASEPROJ_GROUPFIELD_H
#include <utility>
#include "sqlite3.h"
#include "abstractField.h"

class groupField : abstractField {
protected:
    char *group;

public:
    groupField(int id, char *group) : abstractField(id), group(group)
    {
    }

    bool input(sqlite3 *db) override;
};


#endif
