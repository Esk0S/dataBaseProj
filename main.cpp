#include <iostream>
#include <cstring>
#include "sqlite3.h"
#include "idField.h"
#include "nameField.h"
#include "courseField.h"
#include "groupField.h"
#include "facultyField.h"
#include "abstractField.h"
#include <Windows.h>

using namespace std;

bool createTable(sqlite3 *db) {
    char sql_query[] = "CREATE TABLE Stud_info (\n"
                       "    id        INTEGER PRIMARY KEY,\n"
                       "    stud_name TEXT,\n"
                       "    course    INTEGER,\n"
                       "    [group]   TEXT,\n"
                       "    faculty   TEXT\n"
                       ");";
    int rc;
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql_query, -1, &stmt, NULL);

    if(rc != SQLITE_OK)
    {
        if (strcmp(sqlite3_errmsg(db), "table Stud_info already exists") == 0) {
            cerr << "Cannot open prepare statement: " << sqlite3_errmsg(db) << endl;
            return false;
        }
        cerr << "Cannot open prepare statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return false;
    }
    int step = sqlite3_step(stmt);

    while(step == SQLITE_ROW)
    {
        step = sqlite3_step(stmt);
    }
    return true;
}

void menu(sqlite3 *db)
{
    start:;
    while (true) {
        cout << endl;
        cout << "1. Добавить id" << endl;
        cout << "2. Добавить name" << endl;
        cout << "3. Добавить course" << endl;
        cout << "4. Добавить group" << endl;
        cout << "5. Добавить faculty" << endl;
        cout << "6. Вывести строку по ID" << endl;
        cout << "7. Вывести таблицу" << endl;
        cout << "8. Удалить строку" << endl;
        cout << "0. Выход" << endl;
        cout << " > ";
        char a;
        cin >> a;
        cout << endl;
        bool flag = false;
        switch (a)
        {
            case '1':
            {
                int i;
                cout << "Введите ID >";
                cin >> i;
                idField field_id(i);
                field_id.input(db);
                abstractField::output(db, i);
                flag = true;
                goto start;
                break;
            };
            case '2':
            {
                int i;
                char g[200];
                cout << "Введите ID >";
                cin >> i;
                cout << "Введите stud_name >";
                cin >> g;
                nameField field_name(i, g);
                field_name.input(db);
                abstractField::output(db, i);
                flag = true;
                goto start;
                break;
            };
            case '3':
            {
                int i;
                int g;
                cout << "Введите ID >";
                cin >> i;
                cout << "Введите course >";
                cin >> g;
                courseField field_course(i, g);
                field_course.input(db);
                abstractField::output(db, i);
                flag = true;
                goto start;
                break;
            };
            case '4':
            {
                int i;
                char g[200];
                cout << "Введите ID >";
                cin >> i;
                cout << "Введите group >";
                cin >> g;
                groupField field_group(i, g);
                field_group.input(db);
                abstractField::output(db, i);
                flag = true;
                goto start;
                break;
            };
            case '5':
            {
                int i;
                char g[200];
                cout << "Введите ID >";
                cin >> i;
                cout << "Введите faculty >";
                cin >> g;
                facultyField field_faculty(i, g);
                field_faculty.input(db);
                abstractField::output(db, i);
                flag = true;
                goto start;
                break;
            };
            case '6':
            {
                int i;
                cout << "Введите ID >";
                cin >> i;
                abstractField::output(db, i);
                flag = true;
                goto start;
                break;
            };
            case '7':
            {
                abstractField::output_table(db);
                flag = true;
                goto start;
                break;
            }
            case '8':
            {
                int i;
                cout << "Введите ID >";
                cin >> i;
                abstractField::delete_str(db, i);
                abstractField::output_table(db);
                flag = true;
                goto start;
                break;
            }
            case '0':
            {
                exit(0);
            }

        }
        if (flag)
            break;
    }


}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    sqlite3 *db;
    int rc = sqlite3_open("database.db", &db);
    if(rc != SQLITE_OK) {
        cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return 1;
    }

//    createTable(db);


//    idField field_id(7);
//    field_id.input(db);
//    char a[] = "OOP";
//    char b[] = "SAOD";
//    nameField field_name(3, a);
//    field_name.input(db);
//    courseField field_course(7, 3);
//    field_course.input(db);
//    char c[] = "PROG";
//    groupField field_group(7, c);
//    field_group.input(db);
//    char d[] = "TRPO";
//    facultyField field_faculty(7, d);
//    field_faculty.input(db);

    int ids[] {1, 2, 3, 4};
    char names[][30] {"Ivan P", "Ivan N", "George", "GLEB"};
    int course[] {1, 2, 3, 4};
    char group[][30] {"ГФ-11", "ААА-111", "AK-47", "ГОД-11"};
    char faculty[][30] {"Фейсбук", "DURACELL", "МРМ", "Высокий Хротгар"};

    for (int i = 1; i <= 4; i++) {
        idField field_id(i);
        field_id.input(db);
        nameField field_name(i, names[i - 1]);
        field_name.input(db);
        courseField field_course(i, course[i - 1]);
        field_course.input(db);
        groupField field_group(i, group[i - 1]);
        field_group.input(db);
        facultyField field_faculty(i, faculty[i - 1]);
        field_faculty.input(db);
        abstractField::output(db, i);
    }

    menu(db);
//    abstractField::delete_str(db, 1);


    return 0;
}
