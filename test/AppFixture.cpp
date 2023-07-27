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
        app = std::make_shared<App>();
    }
    void TearDown() override {
        app.reset();
    }
    std::shared_ptr<App> app;
};