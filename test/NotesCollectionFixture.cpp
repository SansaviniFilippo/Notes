//
// Created by filippo on 25/07/23.
//

#include "gtest/gtest.h"
#include "../Note.h"
#include "../NotesCollection.h"

class NotesCollectionTest : public ::testing::Test {
protected:
    void SetUp() override {
        note1 = std::make_shared<Note>("Note 1", "Text 1");
        note2 = std::make_shared<Note>("Note 2", "Text 2");
    }
    void TearDown() override {
        note1.reset();
        note2.reset();
    }
    NotesCollection collection = NotesCollection("My Collection");
    std::shared_ptr<Note> note1;
    std::shared_ptr<Note> note2;
};

// AGGIUNTA POST REVISIONE

TEST_F(NotesCollectionTest, BlockedNotesTest) {
    collection.addNote(note1);
    collection.addNote(note2);
    note1->setBlocked(true);
    note2->setBlocked(true);
    EXPECT_EQ(collection.getNoteNumber(), 2);
    EXPECT_EQ(note1->getTitle(), "Note 1");
    EXPECT_EQ(note1->getText(), "Text 1");
    EXPECT_EQ(note2->getTitle(), "Note 2");
    EXPECT_EQ(note2->getText(), "Text 2");

    try {
        collection.editNoteTitle(note1, "New Note 1");
    } catch (std::runtime_error& e) {
        EXPECT_STREQ("ATTENTION :  Note is blocked", e.what());
    }
    EXPECT_EQ(note1->getTitle(), "Note 1");
    try {
        collection.editNoteText(note1, "New Text 1");
    } catch (std::runtime_error& e) {
        EXPECT_STREQ("ATTENTION :  Note is blocked", e.what());
    }
    EXPECT_EQ(note1->getText(), "Text 1");

    try {
        collection.removeNote(note2);
    } catch (std::runtime_error& e) {
        EXPECT_STREQ("ATTENTION :  Note is blocked", e.what());
    }
    EXPECT_EQ(collection.getNoteNumber(), 2);

    EXPECT_EQ(note1->getTitle(), "Note 1");
    EXPECT_EQ(note1->getText(), "Text 1");
    EXPECT_EQ(note2->getTitle(), "Note 2");
    EXPECT_EQ(note2->getText(), "Text 2");

    ::testing::internal::CaptureStdout();
    collection.printAllNotesTitle();
    std::string output = ::testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Notes in My Collection:") != std::string::npos);
    EXPECT_TRUE(output.find("Note 1") != std::string::npos);
    EXPECT_TRUE(output.find("Note 2") != std::string::npos);
}

TEST_F(NotesCollectionTest, AddNoteTest) {
    EXPECT_EQ(collection.getNoteNumber(), 0);
    collection.addNote(note1);
    collection.addNote(note2);
    EXPECT_EQ(collection.getNoteNumber(), 2);
}

TEST_F(NotesCollectionTest, PrintAndRemoveTest) {
    collection.addNote(note1);
    collection.addNote(note2);

    ::testing::internal::CaptureStdout();
    collection.printAllNotesTitle();
    std::string output = ::testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Notes in My Collection:") != std::string::npos);
    EXPECT_TRUE(output.find("Note 1") != std::string::npos);
    EXPECT_TRUE(output.find("Note 2") != std::string::npos);

    ::testing::internal::CaptureStdout();
    collection.printOneNotes(note1);
    output = ::testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Title : Note 1") != std::string::npos);
    EXPECT_TRUE(output.find("Text : Text 1") != std::string::npos);

    ::testing::internal::CaptureStdout();
    collection.printAllNotes();
    output = ::testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Titles and texts of notes in My Collection:") != std::string::npos);
    EXPECT_TRUE(output.find("Title : Note 1") != std::string::npos);
    EXPECT_TRUE(output.find("Text : Text 1") != std::string::npos);
    EXPECT_TRUE(output.find("Title : Note 2") != std::string::npos);
    EXPECT_TRUE(output.find("Text : Text 2") != std::string::npos);

    collection.removeNote(note1);

    ::testing::internal::CaptureStdout();
    collection.printAllNotesTitle();
    output = ::testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Notes in My Collection:") != std::string::npos);
    EXPECT_TRUE(output.find("Note 2") != std::string::npos);

    ::testing::internal::CaptureStdout();
    collection.printAllNotes();
    output = ::testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Titles and texts of notes in My Collection:") != std::string::npos);
    EXPECT_TRUE(output.find("Title : Note 2") != std::string::npos);
    EXPECT_TRUE(output.find("Text : Text 2") != std::string::npos);

    collection.removeNote(note2);

    ::testing::internal::CaptureStdout();
    collection.printAllNotesTitle();
    output = ::testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("No notes in My Collection") != std::string::npos);

    ::testing::internal::CaptureStdout();
    collection.printAllNotes();
    output = ::testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("No notes in My Collection") != std::string::npos);
}

TEST_F(NotesCollectionTest, EditTitleAndTextTest) {
    collection.addNote(note1);
    collection.editNoteTitle(note1, "New Note 1");
    EXPECT_EQ(note1->getTitle(), "New Note 1");
    collection.editNoteText(note1, "New Text 1");
    EXPECT_EQ(note1->getText(), "New Text 1");
}

TEST_F(NotesCollectionTest, BlockedTest) {
    auto note3 = std::make_shared<Note>("Note 3", "Text 3", false);
    collection.addNote(note3);
    EXPECT_FALSE(note3->isBlocked());

    collection.block(note3);
    EXPECT_TRUE(note3->isBlocked());

    collection.unblock(note3);
    EXPECT_FALSE(note3->isBlocked());
}

TEST_F(NotesCollectionTest, GetterAndSetterTest) {
    EXPECT_EQ(collection.getName(), "My Collection");
    collection.setName("New My Collection");
    EXPECT_EQ(collection.getName(), "New My Collection");
}

TEST_F(NotesCollectionTest, PrintRemovedNotesTest) {
    collection.addNote(note1);
    collection.addNote(note2);

    ::testing::internal::CaptureStdout();
    collection.printAllRemovedNotesTitle();
    std::string output = ::testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("No removed notes in My Collection's bin") != std::string::npos);

    ::testing::internal::CaptureStdout();
    collection.printAllRemovedNotes();
    output = ::testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("No removed notes in My Collection's bin") != std::string::npos);

    collection.removeNote(note2);

    ::testing::internal::CaptureStdout();
    collection.printAllRemovedNotesTitle();
    output = ::testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Removed Notes in My Collection's bin:") != std::string::npos);
    EXPECT_TRUE(output.find("Note 2") != std::string::npos);

    ::testing::internal::CaptureStdout();
    collection.printAllRemovedNotes();
    output = ::testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Titles and texts of removed notes in My Collection's bin:") != std::string::npos);
    EXPECT_TRUE(output.find("Title : Note 2") != std::string::npos);
    EXPECT_TRUE(output.find("Text : Text 2") != std::string::npos);

    collection.removeNote(note1);

    ::testing::internal::CaptureStdout();
    collection.printAllRemovedNotesTitle();
    output = ::testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Removed Notes in My Collection's bin:") != std::string::npos);
    EXPECT_TRUE(output.find("Note 2") != std::string::npos);
    EXPECT_TRUE(output.find("Note 1") != std::string::npos);

    ::testing::internal::CaptureStdout();
    collection.printAllRemovedNotes();
    output = ::testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Titles and texts of removed notes in My Collection's bin:") != std::string::npos);
    EXPECT_TRUE(output.find("Title : Note 2") != std::string::npos);
    EXPECT_TRUE(output.find("Text : Text 2") != std::string::npos);
    EXPECT_TRUE(output.find("Title : Note 1") != std::string::npos);
    EXPECT_TRUE(output.find("Text : Text 1") != std::string::npos);

    collection.emptyTheBin();
    ::testing::internal::CaptureStdout();
    collection.printAllRemovedNotesTitle();
    output = ::testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("No removed notes in My Collection's bin") != std::string::npos);

    ::testing::internal::CaptureStdout();
    collection.printAllRemovedNotes();
    output = ::testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("No removed notes in My Collection's bin") != std::string::npos);
}

TEST_F(NotesCollectionTest, emptyTheBinTest) {
    collection.addNote(note1);
    collection.addNote(note2);
    EXPECT_EQ(collection.getRemovedNoteNumber(), 0);

    collection.removeNote(note1);
    collection.removeNote(note2);
    EXPECT_EQ(collection.getRemovedNoteNumber(), 2);

    collection.emptyTheBin();
    EXPECT_EQ(collection.getRemovedNoteNumber(), 0);
}

TEST_F(NotesCollectionTest, ClearCollectionTest) {
    collection.addNote(note1);
    collection.addNote(note2);

    EXPECT_EQ(collection.getNoteNumber(), 2);
    EXPECT_EQ(collection.getRemovedNoteNumber(), 0);

    collection.clearCollection();

    EXPECT_EQ(collection.getNoteNumber(), 0);
    EXPECT_EQ(collection.getRemovedNoteNumber(), 2);
}

TEST_F(NotesCollectionTest, ExceptionThrowTest) {
    collection.addNote(note1);
    EXPECT_THROW(collection.addNote(note1), std::runtime_error);
    try {
        collection.addNote(note1);
    } catch (std::runtime_error& e) {
        EXPECT_STREQ("ATTENTION :  Note already exists in this collection", e.what());
    }

    note1->setBlocked(true);
    EXPECT_THROW(collection.removeNote(note1), std::runtime_error);
    try {
        collection.removeNote(note1);
    } catch (std::runtime_error& e) {
        EXPECT_STREQ("ATTENTION :  Note is blocked", e.what());
    }

    collection.unblock(note1);
    collection.removeNote(note1);
    EXPECT_THROW(collection.removeNote(note1), std::runtime_error);
    try {
        collection.removeNote(note1);
    } catch (std::runtime_error& e) {
        EXPECT_STREQ("ATTENTION :  Note not found in this collection", e.what());
    }

    EXPECT_THROW(collection.printOneNotes(note1), std::runtime_error);
    try {
        collection.printOneNotes(note1);
    } catch (std::runtime_error& e) {
        EXPECT_STREQ("ATTENTION :  Note not found in this collection", e.what());
    }

    EXPECT_THROW(collection.editNoteTitle(note1, "New title"), std::runtime_error);
    try {
        collection.editNoteTitle(note1, "New title");
    } catch (std::runtime_error& e) {
        EXPECT_STREQ("ATTENTION :  Note not found in this collection", e.what());
    }

    EXPECT_THROW(collection.editNoteText(note1, "New text"), std::runtime_error);
    try {
        collection.editNoteText(note1, "New text");
    } catch (std::runtime_error& e) {
        EXPECT_STREQ("ATTENTION :  Note not found in this collection", e.what());
    }

    EXPECT_THROW(collection.block(note1), std::runtime_error);
    try {
        collection.block(note1);
    } catch (std::runtime_error& e) {
        EXPECT_STREQ("ATTENTION :  Note not found in this collection", e.what());
    }

    EXPECT_THROW(collection.unblock(note1), std::runtime_error);
    try {
        collection.unblock(note1);
    } catch (std::runtime_error& e) {
        EXPECT_STREQ("ATTENTION :  Note not found in this collection", e.what());
    }

    collection.addNote(note1);
    collection.block(note1);
    EXPECT_THROW(collection.editNoteTitle(note1, "New title"), std::runtime_error);
    try {
        collection.editNoteTitle(note1, "New title");
    } catch (std::runtime_error& e) {
        EXPECT_STREQ("ATTENTION :  Note is blocked", e.what());
    }

    EXPECT_THROW(collection.editNoteText(note1, "New text"), std::runtime_error);
    try {
        collection.editNoteText(note1, "New text");
    } catch (std::runtime_error& e) {
        EXPECT_STREQ("ATTENTION :  Note is blocked", e.what());
    }

    EXPECT_THROW(collection.block(note1), std::runtime_error);
    try {
        collection.block(note1);
    } catch (std::runtime_error& e) {
        EXPECT_STREQ("ATTENTION :  Note is already blocked", e.what());
    }

    collection.unblock(note1);
    EXPECT_THROW(collection.unblock(note1), std::runtime_error);
    try {
        collection.unblock(note1);
    } catch (std::runtime_error& e) {
        EXPECT_STREQ("ATTENTION :  Note is already unblocked", e.what());
    }

    collection.clearCollection();
    EXPECT_THROW(collection.clearCollection(), std::runtime_error);
    try {
        collection.clearCollection();
    } catch (std::runtime_error& e) {
        EXPECT_STREQ("ATTENTION :  Collection is already empty", e.what());
    }

    collection.emptyTheBin();
    EXPECT_THROW(collection.emptyTheBin(), std::runtime_error);
    try {
        collection.emptyTheBin();
    } catch (std::runtime_error& e) {
        EXPECT_STREQ("ATTENTION :  Bin is already empty", e.what());
    }
}