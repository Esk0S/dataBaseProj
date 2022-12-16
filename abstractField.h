#ifndef DATABASEPROJ_ABSTRACTFIELD_H
#define DATABASEPROJ_ABSTRACTFIELD_H
#include <iostream>
#include <string>
#include <utility>
#include "sqlite3.h"
#include <cstring>

using namespace std;

class abstractField {
protected:
    int id;

private:
    struct Result
    {
        int id;
        char* stud_name;
        int course;
        char* group;
        char* faculty;
    };

public:
    explicit abstractField(int id) : id(id)
    {
    }
    virtual bool input(sqlite3 *db) = 0;
    static bool output(sqlite3 *db, int _id);
};

#endif