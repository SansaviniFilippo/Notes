//
// Created by filippo on 21/07/23.
//

#include "App.h"

App::App(std::unique_ptr<NotesCollection> s) : subject(std::move(s)) {
    attach();
}

App::~App() {
    detach();
}

void App::attach() {
    subject->subscribe(this);
}

void App::detach() {
    subject->unsubscribe(this);
}