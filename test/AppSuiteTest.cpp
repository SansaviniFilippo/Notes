//
// Created by filippo on 25/07/23.
//

#include "gtest/gtest.h"
#include "../Note.h"
#include "../NotesCollection.h"
#include "../ImportantNotesCollection.h"
#include "../App.h"

TEST(AppSuiteTest, UpdateTest) {
    App app;
    NotesCollection collection1("My Collection 1");
    NotesCollection collection2("My Collection 2");
    ImportantNotesCollection importantCollection("My Important Collection");
    auto note1 = std::make_shared<Note>("Title 1", "Text 1", false);
    auto note2 = std::make_shared<Note>("Title 2", "Text 2", false);
    auto note3 = std::make_shared<Note>("Title 3", "Text 3", true);
    collection1.addNote(note1);
    collection1.addNote(note2);
    importantCollection.addImportantNote(note3);

    app.attach(&collection1);
    app.attach(&collection2);
    app.attach(&importantCollection);

    ::testing::internal::CaptureStdout();
    app.update();
    std::string output = ::testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Collection My Collection 1 has: 2 notes.") != std::string::npos);
    EXPECT_TRUE(output.find("Collection My Collection 2 has: 0 notes.") != std::string::npos);
    EXPECT_TRUE(output.find("Important collection My Important Collection has: 1 important note.") != std::string::npos);

    app.detach(&collection1);
    app.detach(&collection2);
    app.detach(&importantCollection);
}

TEST(AppSuiteTest, AttachAndDetachTest) {
    App app;
    NotesCollection collection1("My Collection 1");
    NotesCollection collection2("My Collection 2");
    ImportantNotesCollection importantCollection("My Important Collection");

    app.attach(&collection1);
    app.attach(&collection2);

    EXPECT_EQ(app.getCollectionsNumber(), 2);

    app.attach(&importantCollection);
    EXPECT_EQ(app.getCollectionsNumber(), 3);

    app.detach(&collection2);
    EXPECT_EQ(app.getCollectionsNumber(), 2);

    app.detach(&collection1);
    app.detach(&importantCollection);
    EXPECT_EQ(app.getCollectionsNumber(), 0);
}