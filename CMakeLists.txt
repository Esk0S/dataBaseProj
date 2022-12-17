cmake_minimum_required(VERSION 3.23)
project(dataBaseProj)

set(CMAKE_CXX_STANDARD 14)

add_executable(dataBaseProj main.cpp abstractField.h idField.cpp idField.h sqlite3.c sqlite3.h abstractField.cpp nameField.cpp nameField.h courseField.cpp courseField.h groupField.cpp groupField.h facultyField.cpp facultyField.h)
find_package (SQLite3)

if (SQLITE3_FOUND)
    include_directories(${SQLITE3_INCLUDE_DIRS})
    target_link_libraries (tutorial ${SQLITE3_LIBRARIES})
endif (SQLITE3_FOUND)