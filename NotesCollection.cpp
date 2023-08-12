//
// Created by filippo on 20/07/23.
//

#include "NotesCollection.h"

void NotesCollection::addNote(std::shared_ptr<Note> note) {
    bool found = false;
    for(auto & it : collection) {
        if (it->getTitle() == note->getTitle())
            found = true;
    }
    if(!found) {
        for(auto & it : removedNotesCollection) {
            if (it->getTitle() == note->getTitle()) {
                removeRemovedNote(note);
                return;
            }
        }
        collection.push_back(std::move(note));
        noteNumber++;
        notify();
    }
    else
        throw std::runtime_error("ATTENTION :  Note already exists in this collection");
}

void NotesCollection::removeNote(const std::shared_ptr<Note>& note) {
    for(auto it = collection.begin(); it != collection.end(); it++) {
        if ((*it)->getTitle() == note->getTitle()) {
            if((*it)->isBlocked())
                throw std::runtime_error("ATTENTION :  Note is blocked");
            else {
                addRemovedNote(note);
                collection.erase(it);
                noteNumber--;
                notify();
                return;
            }
        }
    }
}

void NotesCollection::printAllNotesTitle() const {
    std::cout << "Notes in " << name << ":" << std::endl;
    for(auto & it : collection)
        std::cout << it->getTitle() << std::endl;
}

void NotesCollection::printAllNotes() const {
    std::cout << "Titles and texts of notes in " << name << ":" << std::endl;
    for(auto & it : collection) {
        std::cout << "Title : " << it->getTitle() << std::endl;
        std::cout << "Text : " << it->getText() << std::endl;
    }
}

std::string NotesCollection::getName() const {
    return name;
}

void NotesCollection::setName(std::string n) {
    name = std::move(n);
}

void NotesCollection::printOneNotes(const std::shared_ptr<Note>& note) const {
    for(auto & it : collection) {
        if (it->getTitle() == note->getTitle()) {
            std::cout << "Title : " << it->getTitle() << std::endl;
            std::cout << "Text : " << it->getText() << std::endl;
            return;
        }
    }
    throw std::runtime_error("ATTENTION :  Note not found in this collection");
}

void NotesCollection::editNoteTitle(const std::shared_ptr<Note>& note, std::string newTitle) {
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
    throw std::runtime_error("ATTENTION :  Note not found in this collection");
}

void NotesCollection::editNoteText(const std::shared_ptr<Note>& note, std::string newText) {
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
    throw std::runtime_error("ATTENTION :  Note not found in this collection");
}

void NotesCollection::subscribe(Observer* o) {
    observers.push_back(o);
}

void NotesCollection::unsubscribe(Observer* o) {
    observers.remove(o);
}

void NotesCollection::notify() {
    for(auto & observer : observers)
        observer->update();
}

void NotesCollection::block(const std::shared_ptr<Note>& note) {
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
    throw std::runtime_error("ATTENTION :  Note not found in this collection");
}

void NotesCollection::unblock(const std::shared_ptr<Note>& note) {
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
    throw std::runtime_error("ATTENTION :  Note not found in this collection");
}

int NotesCollection::getNoteNumber() const {
    return noteNumber;
}

void NotesCollection::printAllRemovedNotesTitle() const {
    std::cout << "Removed Notes in " << name << "'s bin:" << std::endl;
    for(auto & it : removedNotesCollection)
        std::cout << it->getTitle() << std::endl;
}

void NotesCollection::printAllRemovedNotes() const {
    std::cout << "Titles and texts of removed notes in " << name << "'s bin:" << std::endl;
    for(auto & it : removedNotesCollection) {
        std::cout << "Title : " << it->getTitle() << std::endl;
        std::cout << "Text : " << it->getText() << std::endl;
    }
}

void NotesCollection::addRemovedNote(std::shared_ptr<Note> note) {
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

void NotesCollection::removeRemovedNote(const std::shared_ptr<Note>& note) {
    for(auto it = removedNotesCollection.begin(); it != removedNotesCollection.end(); it++) {
        if ((*it)->getTitle() == note->getTitle()) {
            removedNotesCollection.erase(it);
            removedNoteNumber--;
            return;
        }
    }
}

void NotesCollection::emptyTheBin() {
    if(removedNotesCollection.empty())
        throw std::runtime_error("ATTENTION :  Bin is already empty");
    else {
        removedNotesCollection.clear();
        removedNoteNumber = 0;
    }
}

void NotesCollection::clearCollection() {
    if(collection.empty())
        throw std::runtime_error("ATTENTION :  Collection is already empty");
    else {
        for (auto &it: collection)
            addRemovedNote(it);
        collection.clear();
        noteNumber = 0;
        notify();
    }
}

int NotesCollection::getRemovedNoteNumber() const {
    return removedNoteNumber;
}