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

TEST_F(NotesCollectionTest, RemoveNoteTest) {
    auto note1 = std::make_shared<Note>("Note 1", "Text 1");
    auto note2 = std::make_shared<Note>("Note 2", "Text 2");
    collection->addNote(note1);
    collection->addNote(note2);
    collection->removeNote(note1);
    EXPECT_EQ(collection->getNoteNumber(), 1);
}