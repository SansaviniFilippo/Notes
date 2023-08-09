//
// Created by filippo on 25/07/23.
//

#include "gtest/gtest.h"
#include "../Note.h"

TEST(NotesTests, GetterAndSetterTest) {
    auto note = std::make_unique<Note>("Title", "Text", false);
    EXPECT_EQ(note->getTitle(), "Title");
    EXPECT_EQ(note->getText(), "Text");
    EXPECT_FALSE(note->isBlocked());

    note->setTitle("New Title");
    note->setText("New Text");
    note->setBlocked(true);
    EXPECT_EQ(note->getTitle(), "New Title");
    EXPECT_EQ(note->getText(), "New Text");
    EXPECT_TRUE(note->isBlocked());
}

TEST(NotesTests, EmptyInitializationTest) {
    auto note = std::make_unique<Note>("","");
    EXPECT_EQ(note->getTitle(), "");
    EXPECT_EQ(note->getText(), "");
    EXPECT_FALSE(note->isBlocked());
}