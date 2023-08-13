//
// Created by filippo on 25/07/23.
//

#include "gtest/gtest.h"
#include "../Note.h"
#include "../NotesCollection.h"
#include "../ImportantNotesCollection.h"
#include "../App.h"

class AppFixtureTest : public ::testing::Test {
protected:
    void SetUp() override {
        note1 = std::make_shared<Note>("Title 1", "Text 1", false);
        note2 = std::make_shared<Note>("Title 2", "Text 2", false);
        note3 = std::make_shared<Note>("Title 3", "Text 3", true);

        collection1.addNote(note1);
        collection1.addNote(note2);
        importantCollection.addImportantNote(note3);
    }
    void TearDown() override {
        note1.reset();
        note2.reset();
        note3.reset();
    }
    App app;
    NotesCollection collection1{"My Collection 1"};
    NotesCollection collection2{"My Collection 2"};
    ImportantNotesCollection importantCollection{"My Important Collection"};
    std::shared_ptr<Note> note1;
    std::shared_ptr<Note> note2;
    std::shared_ptr<Note> note3;
};

TEST_F(AppFixtureTest, UpdateTest) {
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

    EXPECT_THROW(app.update(), std::runtime_error);
    try {
        app.update();
    } catch (const std::runtime_error& e) {
        EXPECT_STREQ(e.what(), "ATTENTION : No collections attached");
    }
}

TEST_F(AppFixtureTest, AttachAndDetachTest) {
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

TEST_F(AppFixtureTest, AttachAndDetachExceptionTest) {
    app.attach(&collection1);
    app.attach(&collection2);
    app.attach(&importantCollection);

    EXPECT_THROW(app.attach(&collection1), std::invalid_argument);
    try {
        app.attach(&collection1);
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ(e.what(), "ATTENTION : Subject already attached");
    }
    EXPECT_THROW(app.attach(&collection2), std::invalid_argument);
    try {
        app.attach(&collection2);
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ(e.what(), "ATTENTION : Subject already attached");
    }
    EXPECT_THROW(app.attach(&importantCollection), std::invalid_argument);
    try {
        app.attach(&importantCollection);
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ(e.what(), "ATTENTION : Subject already attached");
    }

    app.detach(&collection1);
    app.detach(&collection2);
    app.detach(&importantCollection);

    EXPECT_THROW(app.detach(&collection1), std::invalid_argument);
    try {
        app.detach(&collection1);
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ(e.what(), "ATTENTION : Subject not attached");
    }
    EXPECT_THROW(app.detach(&collection2), std::invalid_argument);
    try {
        app.detach(&collection2);
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ(e.what(), "ATTENTION : Subject not attached");
    }
    EXPECT_THROW(app.detach(&importantCollection), std::invalid_argument);
    try {
        app.detach(&importantCollection);
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ(e.what(), "ATTENTION : Subject not attached");
    }
}