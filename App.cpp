//
// Created by filippo on 21/07/23.
//

#include <algorithm>
#include "App.h"

App::~App() = default;

void App::update() {
    for(auto it = collections.begin(); it != collections.end(); it++) {
        auto* collection = dynamic_cast<NotesCollection*>(it->second);
        if(collection) {
            if(collection->getNoteNumber() == 1)
                std::cout << "Collection " << collection->getName() << " has : 1 note." << std::endl;
            else
                std::cout << "Collection " << collection->getName() << " has : " << collection->getNoteNumber() << " notes." << std::endl;
        }
    }
}

void App::attach(Subject* subject) {
    auto* collection = dynamic_cast<NotesCollection*>(subject);
    collections.insert(std::pair<std::string, Subject*>(collection->getName(), subject));
    collection->subscribe(this);
}

void App::detach(Subject* subject) {
    auto* collection = dynamic_cast<NotesCollection*>(subject);
    collections.erase(collection->getName());
    collection->unsubscribe(this);
}