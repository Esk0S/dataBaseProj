#ifndef DATABASEPROJ_STUDFIELD_H
#define DATABASEPROJ_STUDFIELD_H
#include <utility>
#include "sqlite3.h"
#include "abstractField.h"

class idField : public abstractField {

public:
    explicit idField(int id) : abstractField(id)
    {
    }

    bool input(sqlite3 *db) override;
//    bool output() override;
};


#endif
