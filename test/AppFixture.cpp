//
// Created by filippo on 25/07/23.
//

#include "gtest/gtest.h"
#include "../Note.h"
#include "../NotesCollection.h"
#include "../ImportantNotesCollection.h"
#include "../App.h"

class AppTest : public ::testing::Test {
protected:
    void SetUp() override {
        app = std::make_unique<App>();
        collection1 = std::make_unique<NotesCollection>("My Collection 1");
        collection2 = std::make_unique<NotesCollection>("My Collection 2");
        importantCollection = std::make_unique<ImportantNotesCollection>("My Important Collection");
        note1 = std::make_shared<Note>("Title 1", "Text 1");
        note2 = std::make_shared<Note>("Title 2", "Text 2");
        note3 = std::make_shared<Note>("Title 3", "Text 3");
    }
    void TearDown() override {
        app.reset();
    }
    std::unique_ptr<App> app;
    std::shared_ptr<Note> note1;
    std::shared_ptr<Note> note2;
    std::shared_ptr<Note> note3;
    std::unique_ptr<NotesCollection> collection1;
    std::unique_ptr<NotesCollection> collection2;
    std::unique_ptr<ImportantNotesCollection> importantCollection;
};

TEST_F(AppTest, UpdateTest) {
    collection1->addNote(note1);
    collection1->addNote(note2);
    importantCollection->addImportantNote(note3);

    app->attach(collection1.get());
    app->attach(collection2.get());
    app->attach(importantCollection.get());

    ::testing::internal::CaptureStdout();
    app->update();
    std::string output = ::testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("Collection My Collection 1 has: 2 notes.") != std::string::npos);
    EXPECT_TRUE(output.find("Collection My Collection 2 has: 0 notes.") != std::string::npos);
    EXPECT_TRUE(output.find("Important collection My Important Collection has: 1 important note.") != std::string::npos);

    app->detach(collection1.get());
    app->detach(collection2.get());
    app->detach(importantCollection.get());
}

TEST_F(AppTest, AttachAndDetachTest) {
    app->attach(collection1.get());
    app->attach(collection2.get());

    EXPECT_EQ(app->getCollectionsNumber(), 2);

    app->attach(importantCollection.get());
    EXPECT_EQ(app->getCollectionsNumber(), 3);

    app->detach(collection2.get());
    EXPECT_EQ(app->getCollectionsNumber(), 2);

    app->detach(collection1.get());
    app->detach(importantCollection.get());
    EXPECT_EQ(app->getCollectionsNumber(), 0);
}