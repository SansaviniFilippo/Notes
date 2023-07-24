//
// Created by filippo on 21/07/23.
//

#include <algorithm>
#include "App.h"

void App::update() {
    for (const auto& it : collections) {
        auto collection = dynamic_cast<NotesCollection*>(it);
        if (collection) {
            if (collection->getNoteNumber() == 1)
                std::cout << "Collection " << collection->getName() << " has: 1 note." << std::endl;
            else
                std::cout << "Collection " << collection->getName() << " has: " << collection->getNoteNumber() << " notes." << std::endl;
        }
        auto importantCollection = dynamic_cast<ImportantNotesCollection*>(it);
        if (importantCollection) {
            if (importantCollection->getNoteNumber() == 1)
                std::cout << "Important collection " << importantCollection->getName() << " has: 1 important note." << std::endl;
            else
                std::cout << "Important collection " << importantCollection->getName() << " has: " << importantCollection->getNoteNumber() << " important notes." << std::endl;
        }
    }
}

void App::attach(Subject* subject) {
    collections.push_back(subject);
    collections.back()->subscribe(this);
}

void App::detach(Subject* subject) {
    collections.back()->unsubscribe(this);
    collections.remove(subject);
}