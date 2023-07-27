cmake_minimum_required(VERSION 3.5)

add_subdirectory(./lib/googletest/)
set(gtest_SOURCE_DIR, ./lib/googletest/)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_SOURCE_FILES runAllTests.cpp NotesFixture.cpp NotesCollectionFixture.cpp ImportantNotesCollectionFixture.cpp AppFixture.cpp)
add_executable(runNotesTests ${TEST_SOURCE_FILES})
target_link_libraries(runNotesTests gtest gtest_main core)