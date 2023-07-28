//
// Created by filippo on 25/07/23.
//

#include "gtest/gtest.h"
#include "../Note.h"
#include "../ImportantNotesCollection.h"

class ImportantNotesCollectionTest : public ::testing::Test {
protected:
    void SetUp() override {
        collection = std::make_shared<ImportantNotesCollection>("My Important Collection");
        note1 = std::make_shared<Note>("Important Note 1", "Important Text 1");
        note2 = std::make_shared<Note>("Important Note 2", "Important Text 2");
        note3 = std::make_shared<Note>("Important Note 3", "Important Text 3");
    }
    void TearDown() override {
        collection.reset();
        note1.reset();
        note2.reset();
    }
    std::shared_ptr<ImportantNotesCollection> collection;
    std::shared_ptr<Note> note1;
    std::shared_ptr<Note> note2;
    std::shared_ptr<Note> note3;
};


TEST_F(ImportantNotesCollectionTest, AddNoteTest) {
    collection->addImportantNote(note1);
    EXPECT_EQ(collection->getNoteNumber(), 1);
    collection->addImportantNote(note2);
    collection->addImportantNote(note3);
    EXPECT_EQ(collection->getNoteNumber(), 3);
}

TEST_F(ImportantNotesCollectionTest, RemoveNoteTest) {
    collection->addImportantNote(note1);
    collection->addImportantNote(note2);
    collection->printOneImportantNotes(note1);
    collection->printAllImportantNotes();
    collection->printAllImportantNotesTitle();
    collection->removeImportantNote(note1);
    EXPECT_EQ(collection->getNoteNumber(), 1);
    collection->printAllImportantNotesTitle();
}

TEST_F(ImportantNotesCollectionTest, UpdateTest) {
    collection->addImportantNote(note1);
    collection->editImportantNoteTitle(note1, "New Note 1");
    EXPECT_EQ(note1->getTitle(), "New Note 1");
    collection->editImportantNoteText(note1, "New Text 1");
    EXPECT_EQ(note1->getText(), "New Text 1");
}

TEST_F(ImportantNotesCollectionTest, BlockedTest) {
    auto note4 = std::make_shared<Note>("Note 4", "Text 4", false);
    collection->addImportantNote(note1);
    EXPECT_FALSE(note1->isBlocked());
    collection->blockImportantNotes(note1);
    EXPECT_TRUE(note1->isBlocked());
    collection->unblockImportantNotes(note1);
    EXPECT_FALSE(note1->isBlocked());
}

TEST_F(ImportantNotesCollectionTest, GetterTest) {
    EXPECT_EQ(collection->getName(), "My Important Collection");
}