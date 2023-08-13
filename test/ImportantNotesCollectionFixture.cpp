//
// Created by filippo on 25/07/23.
//

#include "gtest/gtest.h"
#include "../Note.h"
#include "../ImportantNotesCollection.h"

class ImportantNotesCollectionTest : public ::testing::Test {
protected:
    void SetUp() override {
        collection = ImportantNotesCollection("My Important Collection");
        note1 = std::make_shared<Note>("Important Note 1", "Important Text 1");
        note2 = std::make_shared<Note>("Important Note 2", "Important Text 2");
        note3 = std::make_shared<Note>("Important Note 3", "Important Text 3");
    }
    void TearDown() override {
        note1.reset();
        note2.reset();
        note3.reset();
    }
    ImportantNotesCollection collection;
    std::shared_ptr<Note> note1;
    std::shared_ptr<Note> note2;
    std::shared_ptr<Note> note3;
};

TEST_F(ImportantNotesCollectionTest, AddNoteTest) {
    collection.addImportantNote(note1);
    EXPECT_EQ(collection.getNoteNumber(), 1);
    collection.addImportantNote(note2);
    collection.addImportantNote(note3);
    EXPECT_EQ(collection.getNoteNumber(), 3);
}

TEST_F(ImportantNotesCollectionTest, PrintAndRemoveNoteTest) {
    collection.addImportantNote(note1);
    collection.addImportantNote(note2);

    ::testing::internal::CaptureStdout();
    collection.printAllImportantNotesTitle();
    std::string output = ::testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Important notes in My Important Collection:") != std::string::npos);
    EXPECT_TRUE(output.find("Important Note 1") != std::string::npos);
    EXPECT_TRUE(output.find("Important Note 2") != std::string::npos);

    ::testing::internal::CaptureStdout();
    collection.printAllImportantNotes();
    output = ::testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Titles and texts of important notes in My Important Collection:") != std::string::npos);
    EXPECT_TRUE(output.find("Title : Important Note 1") != std::string::npos);
    EXPECT_TRUE(output.find("Text : Important Text 1") != std::string::npos);
    EXPECT_TRUE(output.find("Title : Important Note 2") != std::string::npos);
    EXPECT_TRUE(output.find("Text : Important Text 2") != std::string::npos);

    collection.removeImportantNote(note1);

    ::testing::internal::CaptureStdout();
    collection.printAllImportantNotesTitle();
    output = ::testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Important notes in My Important Collection:") != std::string::npos);
    EXPECT_TRUE(output.find("Important Note 2") != std::string::npos);

    ::testing::internal::CaptureStdout();
    collection.printAllImportantNotes();
    output = ::testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Titles and texts of important notes in My Important Collection:") != std::string::npos);
    EXPECT_TRUE(output.find("Title : Important Note 2") != std::string::npos);
    EXPECT_TRUE(output.find("Text : Important Text 2") != std::string::npos);

    collection.removeImportantNote(note2);

    ::testing::internal::CaptureStdout();
    collection.printAllImportantNotesTitle();
    output = ::testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("No important notes in My Important Collection") != std::string::npos);

    ::testing::internal::CaptureStdout();
    collection.printAllImportantNotes();
    output = ::testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("No important notes in My Important Collection") != std::string::npos);
}

TEST_F(ImportantNotesCollectionTest, PrintRemovedImportantNotesTest) {
    collection.addImportantNote(note1);
    collection.addImportantNote(note2);

    ::testing::internal::CaptureStdout();
    collection.printAllRemovedImportantNotesTitle();
    std::string output = ::testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("No removed important notes in My Important Collection's bin") != std::string::npos);

    ::testing::internal::CaptureStdout();
    collection.printAllRemovedImportantNotes();
    output = ::testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("No removed important notes in My Important Collection's bin") != std::string::npos);

    collection.removeImportantNote(note2);

    ::testing::internal::CaptureStdout();
    collection.printAllRemovedImportantNotesTitle();
    output = ::testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Removed important notes in My Important Collection's bin") != std::string::npos);
    EXPECT_TRUE(output.find("Important Note 2") != std::string::npos);

    ::testing::internal::CaptureStdout();
    collection.printAllRemovedImportantNotes();
    output = ::testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Titles and texts of removed important notes in My Important Collection's bin") != std::string::npos);
    EXPECT_TRUE(output.find("Title : Important Note 2") != std::string::npos);
    EXPECT_TRUE(output.find("Text : Important Text 2") != std::string::npos);

    collection.removeImportantNote(note1);

    ::testing::internal::CaptureStdout();
    collection.printAllRemovedImportantNotesTitle();
    output = ::testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Removed important notes in My Important Collection's bin") != std::string::npos);
    EXPECT_TRUE(output.find("Important Note 2") != std::string::npos);
    EXPECT_TRUE(output.find("Important Note 1") != std::string::npos);

    ::testing::internal::CaptureStdout();
    collection.printAllRemovedImportantNotes();
    output = ::testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Titles and texts of removed important notes in My Important Collection's bin") != std::string::npos);
    EXPECT_TRUE(output.find("Title : Important Note 2") != std::string::npos);
    EXPECT_TRUE(output.find("Text : Important Text 2") != std::string::npos);
    EXPECT_TRUE(output.find("Title : Important Note 1") != std::string::npos);
    EXPECT_TRUE(output.find("Text : Important Text 1") != std::string::npos);

    collection.emptyTheBinImportantNotes();
    ::testing::internal::CaptureStdout();
    collection.printAllRemovedImportantNotesTitle();
    output = ::testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("No removed important notes in My Important Collection's bin") != std::string::npos);

    ::testing::internal::CaptureStdout();
    collection.printAllRemovedImportantNotes();
    output = ::testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("No removed important notes in My Important Collection's bin") != std::string::npos);
}

TEST_F(ImportantNotesCollectionTest, UpdateTest) {
    collection.addImportantNote(note1);
    collection.editImportantNoteTitle(note1, "New Note 1");
    EXPECT_EQ(note1->getTitle(), "New Note 1");
    collection.editImportantNoteText(note1, "New Text 1");
    EXPECT_EQ(note1->getText(), "New Text 1");
}

TEST_F(ImportantNotesCollectionTest, BlockedTest) {
    collection.addImportantNote(note1);
    EXPECT_FALSE(note1->isBlocked());

    collection.blockImportantNotes(note1);
    EXPECT_TRUE(note1->isBlocked());

    collection.unblockImportantNotes(note1);
    EXPECT_FALSE(note1->isBlocked());
}

TEST_F(ImportantNotesCollectionTest, GetterTest) {
    EXPECT_EQ(collection.getName(), "My Important Collection");
}


TEST_F(ImportantNotesCollectionTest, removedImportantNotesTest) {
    EXPECT_EQ(collection.getNoteNumber(), 0);
    EXPECT_EQ(collection.getRemovedNoteNumber(), 0);

    collection.addImportantNote(note1);
    EXPECT_EQ(collection.getNoteNumber(), 1);
    EXPECT_EQ(collection.getRemovedNoteNumber(), 0);

    collection.removeImportantNote(note1);
    EXPECT_EQ(collection.getNoteNumber(), 0);
    EXPECT_EQ(collection.getRemovedNoteNumber(), 1);

    collection.addImportantNote(note1);
    EXPECT_EQ(collection.getNoteNumber(), 1);
    EXPECT_EQ(collection.getRemovedNoteNumber(), 0);
}

TEST_F(ImportantNotesCollectionTest, emptyTheBinTest) {
    collection.addImportantNote(note1);
    collection.addImportantNote(note2);
    EXPECT_EQ(collection.getRemovedNoteNumber(), 0);

    collection.removeImportantNote(note1);
    collection.removeImportantNote(note2);
    EXPECT_EQ(collection.getRemovedNoteNumber(), 2);

    collection.emptyTheBinImportantNotes();
    EXPECT_EQ(collection.getRemovedNoteNumber(), 0);
}

TEST_F(ImportantNotesCollectionTest, ClearCollectionTest) {
    collection.addImportantNote(note1);
    collection.addImportantNote(note2);
    EXPECT_EQ(collection.getNoteNumber(), 2);
    EXPECT_EQ(collection.getRemovedNoteNumber(), 0);

    collection.clearCollection();
    EXPECT_EQ(collection.getNoteNumber(), 0);
    EXPECT_EQ(collection.getRemovedNoteNumber(), 2);
}

TEST_F(ImportantNotesCollectionTest, ExceptionThrowTest) {
    collection.addImportantNote(note1);
    EXPECT_THROW(collection.addImportantNote(note1), std::runtime_error);
    try {
        collection.addImportantNote(note1);
    } catch (std::runtime_error& e) {
        EXPECT_STREQ("ATTENTION :  Note already exists in important notes collection", e.what());
    }

    note1->setBlocked(true);
    EXPECT_THROW(collection.removeImportantNote(note1), std::runtime_error);
    try {
        collection.removeImportantNote(note1);
    } catch (std::runtime_error& e) {
        EXPECT_STREQ("ATTENTION :  Note is blocked", e.what());
    }

    collection.unblockImportantNotes(note1);
    collection.removeImportantNote(note1);
    EXPECT_THROW(collection.removeImportantNote(note1), std::runtime_error);
    try {
        collection.removeImportantNote(note1);
    } catch (std::runtime_error& e) {
        EXPECT_STREQ("ATTENTION :  Note not found in important notes collection", e.what());
    }

    EXPECT_THROW(collection.printOneImportantNotes(note1), std::runtime_error);
    try {
        collection.printOneImportantNotes(note1);
    } catch (std::runtime_error& e) {
        EXPECT_STREQ("ATTENTION :  Note not found in important notes collection", e.what());
    }

    EXPECT_THROW(collection.editImportantNoteTitle(note1, "New title"), std::runtime_error);
    try {
        collection.editImportantNoteTitle(note1, "New title");
    } catch (std::runtime_error& e) {
        EXPECT_STREQ("ATTENTION :  Note not found in important notes collection", e.what());
    }

    EXPECT_THROW(collection.editImportantNoteText(note1, "New text"), std::runtime_error);
    try {
        collection.editImportantNoteText(note1, "New text");
    } catch (std::runtime_error& e) {
        EXPECT_STREQ("ATTENTION :  Note not found in important notes collection", e.what());
    }

    EXPECT_THROW(collection.blockImportantNotes(note1), std::runtime_error);
    try {
        collection.blockImportantNotes(note1);
    } catch (std::runtime_error& e) {
        EXPECT_STREQ("ATTENTION :  Note not found in important notes collection", e.what());
    }

    EXPECT_THROW(collection.unblockImportantNotes(note1), std::runtime_error);
    try {
        collection.unblockImportantNotes(note1);
    } catch (std::runtime_error& e) {
        EXPECT_STREQ("ATTENTION :  Note not found in important notes collection", e.what());
    }

    collection.addImportantNote(note1);
    collection.blockImportantNotes(note1);
    EXPECT_THROW(collection.editImportantNoteTitle(note1, "New title"), std::runtime_error);
    try {
        collection.editImportantNoteTitle(note1, "New title");
    } catch (std::runtime_error& e) {
        EXPECT_STREQ("ATTENTION :  Note is blocked", e.what());
    }

    EXPECT_THROW(collection.editImportantNoteText(note1, "New text"), std::runtime_error);
    try {
        collection.editImportantNoteText(note1, "New text");
    } catch (std::runtime_error& e) {
        EXPECT_STREQ("ATTENTION :  Note is blocked", e.what());
    }

    EXPECT_THROW(collection.blockImportantNotes(note1), std::runtime_error);
    try {
        collection.blockImportantNotes(note1);
    } catch (std::runtime_error& e) {
        EXPECT_STREQ("ATTENTION :  Note is already blocked", e.what());
    }

    collection.unblockImportantNotes(note1);
    EXPECT_THROW(collection.unblockImportantNotes(note1), std::runtime_error);
    try {
        collection.unblockImportantNotes(note1);
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

    collection.emptyTheBinImportantNotes();
    EXPECT_THROW(collection.emptyTheBinImportantNotes(), std::runtime_error);
    try {
        collection.emptyTheBinImportantNotes();
    } catch (std::runtime_error& e) {
        EXPECT_STREQ("ATTENTION :  Bin is already empty", e.what());
    }
}