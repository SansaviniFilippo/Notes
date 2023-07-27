//
// Created by filippo on 25/07/23.
//

#include "gtest/gtest.h"
#include "../Note.h"
#include "../NotesCollection.h"

class NotesCollectionTest : public ::testing::Test {
protected:
    void SetUp() override {
        collection = std::make_shared<NotesCollection>("My Collection");
    }
    void TearDown() override {
        collection.reset();
    }
    std::shared_ptr<NotesCollection> collection;
};

TEST_F(NotesCollectionTest, AddNoteTest) {
    collection->addNote(std::make_shared<Note>("Note 1", "Text 1"));
    collection->addNote(std::make_shared<Note>("Note 2", "Text 2"));
    EXPECT_EQ(collection->getNoteNumber(), 2);
}

TEST_F(NotesCollectionTest, PrintAndRemoveTest) {
    auto note1 = std::make_shared<Note>("Note 1", "Text 1");
    auto note2 = std::make_shared<Note>("Note 2", "Text 2");
    collection->addNote(note1);
    collection->addNote(note2);
    collection->printOneNotes(note1);
    collection->printAllNotes();
    collection->printAllNotesTitle();
    collection->removeNote(note1);
    EXPECT_EQ(collection->getNoteNumber(), 1);
    collection->printAllNotesTitle();
}

TEST_F(NotesCollectionTest, UpdateTest) {
    auto note1 = std::make_shared<Note>("Note 1", "Text 1");
    collection->addNote(note1);
    collection->editNoteTitle(note1, "New Note 1");
    EXPECT_EQ(note1->getTitle(), "New Note 1");
    collection->editNoteText(note1, "New Text 1");
    EXPECT_EQ(note1->getText(), "New Text 1");
}

TEST_F(NotesCollectionTest, BlockedTest) {
    auto note1 = std::make_shared<Note>("Note 1", "Text 1", false);
    collection->addNote(note1);
    EXPECT_FALSE(note1->isBlocked());
    collection->block(note1);
    EXPECT_TRUE(note1->isBlocked());
    collection->unblock(note1);
    EXPECT_FALSE(note1->isBlocked());
}