//
// Created by filippo on 21/07/23.
//

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

void App::attach(Subject *collection) {
    collections.push_back(collection);
    collection->subscribe(this);
}

void App::detach(Subject *collection) {
    for(auto it = collections.begin(); it != collections.end(); it++) {
        if(*it == collection) {
            collections.erase(it);
            collection->unsubscribe(this);
            break;
        }
    }
}