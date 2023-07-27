cmake_minimum_required(VERSION 3.5)
project(Notes)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_subdirectory(test)

set(SOURCE_FILES main.cpp Note.cpp Note.h NotesCollection.cpp NotesCollection.h Observer.h Subject.h App.cpp App.h ImportantNotesCollection.cpp ImportantNotesCollection.h)
add_executable(Notes main.cpp)
add_library(core ${SOURCE_FILES})
target_link_libraries(Notes core)