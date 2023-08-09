//
// Created by filippo on 23/07/23.
//

#include "ImportantNotesCollection.h"

#include <utility>

void ImportantNotesCollection::setName(std::string n) {
    name = std::move(n);
}

void ImportantNotesCollection::addImportantNote(std::shared_ptr<Note> note) {
    bool found = false;
    for(auto & it : collection) {
        if (it->getTitle() == note->getTitle())
            found = true;
    }
    if(!found) {
        collection.push_back(std::move(note));
        noteNumber++;
        notify();
    }
    else
        throw std::runtime_error("Note already exists");
}

void ImportantNotesCollection::removeImportantNote(const std::shared_ptr<Note>& note) {
    for(auto it = collection.begin(); it != collection.end(); it++) {
        if ((*it)->getTitle() == note->getTitle()) {
            if((*it)->isBlocked())
                throw std::runtime_error("Note is blocked");
            else {
                collection.erase(it);
                noteNumber--;
                notify();
                return;
            }
        }
    }
}

void ImportantNotesCollection::editImportantNoteTitle(const std::shared_ptr<Note>& note, std::string newTitle) {
    for(auto & it : collection) {
        if (it->getTitle() == note->getTitle()) {
            if(it->isBlocked())
                throw std::runtime_error("Note is blocked");
            else {
                it->setTitle(std::move(newTitle));
                return;
            }
        }
    }
}

void ImportantNotesCollection::editImportantNoteText(const std::shared_ptr<Note>& note, std::string newText) {
    for(auto & it : collection) {
        if (it->getTitle() == note->getTitle()) {
            if(it->isBlocked())
                throw std::runtime_error("Note is blocked");
            else {
                it->setText(std::move(newText));
                return;
            }
        }
    }
}

void ImportantNotesCollection::printAllImportantNotesTitle() {
    std::cout << "Important notes in " << name << ":" << std::endl;
    for(auto & it : collection)
        std::cout << it->getTitle() << std::endl;
}

void ImportantNotesCollection::printAllImportantNotes() {
    std::cout << "Titles and texts of important notes in " << name << ":" << std::endl;
    for(auto & it : collection) {
        std::cout << "Title : " << it->getTitle() << std::endl;
        std::cout << "Text : " << it->getText() << std::endl;
    }
}

void ImportantNotesCollection::printOneImportantNotes(const std::shared_ptr<Note>& note) {
    for(auto & it : collection) {
        if (it->getTitle() == note->getTitle()) {
            std::cout << "Title : " << it->getTitle() << std::endl;
            std::cout << "Text : " << it->getText() << std::endl;
            return;
        }
    }
    throw std::runtime_error("Note not found");
}

void ImportantNotesCollection::blockImportantNotes(const std::shared_ptr<Note>& note) {
    for(auto & it : collection) {
        if (it->getTitle() == note->getTitle()) {
            if(it->isBlocked())
                throw std::runtime_error("Note is already blocked");
            else {
                it->setBlocked(true);
                return;
            }
        }
    }
    throw std::runtime_error("Note not found");
}

void ImportantNotesCollection::unblockImportantNotes(const std::shared_ptr<Note>& note) {
    for(auto & it : collection) {
        if (it->getTitle() == note->getTitle()) {
            if(!it->isBlocked())
                throw std::runtime_error("Note is already unblocked");
            else {
                it->setBlocked(false);
                return;
            }
        }
    }
    throw std::runtime_error("Note not found");
}

std::string ImportantNotesCollection::getName() const {
    return name;
}

int ImportantNotesCollection::getNoteNumber() const {
    return noteNumber;
}

void ImportantNotesCollection::subscribe(Observer *o) {
    observers.push_back(o);
}

void ImportantNotesCollection::unsubscribe(Observer *o) {
    observers.remove(o);
}

void ImportantNotesCollection::notify() {
    for(auto & observer : observers)
        observer->update();
}

void ImportantNotesCollection::printAllRemovedImportantNotesTitle() {
    std::cout << "Removed important notes in " << name << "'s bin:" << std::endl;
    for(auto & it : removedNotesCollection)
        std::cout << it->getTitle() << std::endl;
}

void ImportantNotesCollection::printAllRemovedImportantNotes() {
    std::cout << "Titles and texts of removed important notes in " << name << "'s bin:" << std::endl;
    for(auto & it : removedNotesCollection) {
        std::cout << "Title : " << it->getTitle() << std::endl;
        std::cout << "Text : " << it->getText() << std::endl;
    }
}

void ImportantNotesCollection::addRemovedImportantNotes(std::shared_ptr<Note> note) {
    bool found = false;
    for(auto & it : removedNotesCollection) {
        if (it->getTitle() == note->getTitle())
            found = true;
    }
    if(!found) {
        removedNotesCollection.push_back(std::move(note));
    }
}

void ImportantNotesCollection::removeRemovedImportantNotes(const std::shared_ptr<Note>& note) {
    for(auto it = removedNotesCollection.begin(); it != removedNotesCollection.end(); it++) {
        if ((*it)->getTitle() == note->getTitle()) {
            removedNotesCollection.erase(it);
            return;
        }
    }
}