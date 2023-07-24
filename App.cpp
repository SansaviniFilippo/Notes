//
// Created by filippo on 21/07/23.
//

#include <algorithm>
#include "App.h"

App::~App() = default;

void App::update() {
    for (const auto& subjectPtr : collections) {
        auto* collection = dynamic_cast<NotesCollection*>(subjectPtr.get());
        if (collection) {
            if (collection->getNoteNumber() == 1)
                std::cout << "Collection " << collection->getName() << " has: 1 note." << std::endl;
            else
                std::cout << "Collection " << collection->getName() << " has: " << collection->getNoteNumber() << " notes." << std::endl;
        }
    }
}

void App::attach(std::unique_ptr<Subject> subject) {
    collections.push_back(std::move(subject));
    collections.back()->subscribe(this);
}

void App::detach(std::unique_ptr<Subject> subject) {
    for (auto it = collections.begin(); it != collections.end(); it++) {
        if ((*it).get() == subject.get()) {
            (*it)->unsubscribe(this);
            collections.erase(it);
            return;
        }
    }
}