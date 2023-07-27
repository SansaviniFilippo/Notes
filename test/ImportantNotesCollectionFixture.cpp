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
    }
    void TearDown() override {
        collection.reset();
    }
    std::shared_ptr<ImportantNotesCollection> collection;
};


TEST_F(ImportantNotesCollectionTest, AddNoteTest) {
    collection->addImportantNote(std::make_shared<Note>("Important Note 1", "Important Text"));
    EXPECT_EQ(collection->getNoteNumber(), 1);
    collection->addImportantNote(std::make_shared<Note>("Important Note 2", "Important Text"));
    collection->addImportantNote(std::make_shared<Note>("Important Note 3", "Important Text"));
    EXPECT_EQ(collection->getNoteNumber(), 3);
}

TEST_F(ImportantNotesCollectionTest, RemoveNoteTest) {
    auto note1 = std::make_shared<Note>("Imp Note 1", "Imp Text 1");
    auto note2 = std::make_shared<Note>("Imp Note 2", "Imp Text 2");
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
    auto note1 = std::make_shared<Note>("Note 1", "Text 1");
    collection->addImportantNote(note1);
    collection->editImportantNoteTitle(note1, "New Note 1");
    EXPECT_EQ(note1->getTitle(), "New Note 1");
    collection->editImportantNoteText(note1, "New Text 1");
    EXPECT_EQ(note1->getText(), "New Text 1");
}

TEST_F(ImportantNotesCollectionTest, BlockedTest) {
    auto note1 = std::make_shared<Note>("Note 1", "Text 1", false);
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