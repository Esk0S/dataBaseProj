cmake_minimum_required(VERSION 3.23)
project(dataBaseProj)

set(CMAKE_CXX_STANDARD 14)

add_executable(dataBaseProj main.cpp abstractField.h studField.cpp studField.h idField.cpp idField.h sqlite3.c sqlite3.h abstractField.cpp)
find_package (SQLite3)

if (SQLITE3_FOUND)
    include_directories(${SQLITE3_INCLUDE_DIRS})
    target_link_libraries (tutorial ${SQLITE3_LIBRARIES})
endif (SQLITE3_FOUND)