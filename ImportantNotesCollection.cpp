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
        for(auto & it : removedNotesCollection) {
            if (it->getTitle() == note->getTitle()) {
                removeRemovedImportantNotes(note);
                return;
            }
        }
        collection.push_back(std::move(note));
        noteNumber++;
        notify();
    }
    else
        throw std::runtime_error("ATTENTION :  Note already exists in important notes collection");
}

void ImportantNotesCollection::removeImportantNote(const std::shared_ptr<Note>& note) {
    for(auto it = collection.begin(); it != collection.end(); it++) {
        if ((*it)->getTitle() == note->getTitle()) {
            if((*it)->isBlocked())
                throw std::runtime_error("ATTENTION :  Note is blocked");
            else {
                addRemovedImportantNotes(note);
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
                throw std::runtime_error("ATTENTION :  Note is blocked");
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
                throw std::runtime_error("ATTENTION :  Note is blocked");
            else {
                it->setText(std::move(newText));
                return;
            }
        }
    }
}

void ImportantNotesCollection::printAllImportantNotesTitle() const {
    if (collection.empty())
        std::cout << "No important notes in " << name << std::endl;
    else {
        std::cout << "Important notes in " << name << ":" << std::endl;
        for (auto &it: collection)
            std::cout << it->getTitle() << std::endl;
    }
}

void ImportantNotesCollection::printAllImportantNotes() const {
    if (collection.empty())
        std::cout << "No important notes in " << name << std::endl;
    else {
        std::cout << "Titles and texts of important notes in " << name << ":" << std::endl;
        for(auto & it : collection) {
            std::cout << "Title : " << it->getTitle() << std::endl;
            std::cout << "Text : " << it->getText() << std::endl;
        }
    }
}

void ImportantNotesCollection::printOneImportantNotes(const std::shared_ptr<Note>& note) const {
    for(auto & it : collection) {
        if (it->getTitle() == note->getTitle()) {
            std::cout << "Title : " << it->getTitle() << std::endl;
            std::cout << "Text : " << it->getText() << std::endl;
            return;
        }
    }
    throw std::runtime_error("ATTENTION :  Note not found in important notes collection");
}

void ImportantNotesCollection::blockImportantNotes(const std::shared_ptr<Note>& note) {
    for(auto & it : collection) {
        if (it->getTitle() == note->getTitle()) {
            if(it->isBlocked())
                throw std::runtime_error("ATTENTION :  Note is already blocked");
            else {
                it->setBlocked(true);
                return;
            }
        }
    }
    throw std::runtime_error("ATTENTION :  Note not found in important notes collection");
}

void ImportantNotesCollection::unblockImportantNotes(const std::shared_ptr<Note>& note) {
    for(auto & it : collection) {
        if (it->getTitle() == note->getTitle()) {
            if(!it->isBlocked())
                throw std::runtime_error("ATTENTION :  Note is already unblocked");
            else {
                it->setBlocked(false);
                return;
            }
        }
    }
    throw std::runtime_error("ATTENTION :  Note not found in important notes collection");
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

void ImportantNotesCollection::printAllRemovedImportantNotesTitle() const {
    if (removedNotesCollection.empty())
        std::cout << "No removed important notes in " << name << "'s bin" << std::endl;
    else {
        std::cout << "Removed important notes in " << name << "'s bin:" << std::endl;
        for (auto &it: removedNotesCollection)
            std::cout << it->getTitle() << std::endl;
    }
}

void ImportantNotesCollection::printAllRemovedImportantNotes() const {
    if (removedNotesCollection.empty())
        std::cout << "No removed important notes in " << name << "'s bin" << std::endl;
    else {
        std::cout << "Titles and texts of removed important notes in " << name << "'s bin:" << std::endl;
        for (auto &it: removedNotesCollection) {
            std::cout << "Title : " << it->getTitle() << std::endl;
            std::cout << "Text : " << it->getText() << std::endl;
        }
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
        removedNoteNumber++;
    }
}

void ImportantNotesCollection::removeRemovedImportantNotes(const std::shared_ptr<Note>& note) {
    for(auto it = removedNotesCollection.begin(); it != removedNotesCollection.end(); it++) {
        if ((*it)->getTitle() == note->getTitle()) {
            removedNotesCollection.erase(it);
            removedNoteNumber--;
            return;
        }
    }
}

void ImportantNotesCollection::emptyTheBinImportantNotes() {
    if(removedNotesCollection.empty())
        throw std::runtime_error("ATTENTION :  Bin is already empty");
    else {
        removedNotesCollection.clear();
        removedNoteNumber = 0;
    }
}

void ImportantNotesCollection::clearCollection() {
    if(collection.empty())
        throw std::runtime_error("ATTENTION :  Collection is already empty");
    else {
        for (auto &it: collection)
            addRemovedImportantNotes(it);
        collection.clear();
        noteNumber = 0;
        notify();
    }
}

int ImportantNotesCollection::getRemovedNoteNumber() const {
    return removedNoteNumber;
}