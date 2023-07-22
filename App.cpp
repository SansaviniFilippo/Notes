//
// Created by filippo on 21/07/23.
//

#include <algorithm>
#include "App.h"

App::~App() {
    for(auto it = collections.begin(); it != collections.end(); it++) {
        detach(*it);
    }
}

void App::update() {
    for(auto it = collections.begin(); it != collections.end(); it++) {
        auto* collection = dynamic_cast<NotesCollection*>(*it);
        if(collection) {
            if(collection->getNoteNumber() == 1)
                std::cout << "Collection " << collection->getName() << " has : 1 note." << std::endl;
            else
                std::cout << "Collection " << collection->getName() << " has : " << collection->getNoteNumber() << " notes." << std::endl;
        }
    }
}

void App::attach(Subject* subject) {
    collections.push_back(subject);
    subject->subscribe(this);
}

void App::detach(Subject* subject) {
    auto it = std::find(collections.begin(), collections.end(), subject);
    if (it != collections.end()) {
        subject->unsubscribe(this);
        collections.erase(it);
    }
}