cmake_minimum_required(VERSION 3.25)
project(Notes)

set(CMAKE_CXX_STANDARD 14)

add_executable(Notes main.cpp Note.cpp Note.h NotesCollection.cpp NotesCollection.h Observer.h Subject.h)
