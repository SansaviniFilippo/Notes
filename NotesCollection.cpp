//
// Created by filippo on 20/07/23.
//

#include "NotesCollection.h"

void NotesCollection::addNote(const Note& note) {
    auto it = collection.find(note.getTitle());
    if(it == collection.end())
        collection.insert(std::make_pair(note.getTitle(), note));
    else
        throw std::runtime_error("Note already exists");
}

void NotesCollection::removeNote(std::string noteTitle) {
    auto it = collection.find(noteTitle);
    if(it != collection.end()) {
        if(!(it->second.isBlocked()))
            collection.erase(it);
        else
            throw std::runtime_error("Note is blocked");
    }
    else
        throw std::runtime_error("Note doesn't exist");
}

void NotesCollection::printAllNotesTitle() {
    std::cout << "Notes in " << name << ":" << std::endl;
    for(auto it = collection.begin(); it != collection.end(); it++)
        std::cout << it->first << std::endl;
}

void NotesCollection::printAllNotes() {
    std::cout << "Titles and texts of notes in " << name << ":" << std::endl;
    for(auto it = collection.begin(); it != collection.end(); it++) {
        std::cout << "Title : " << it->second.getTitle() << std::endl;
        std::cout << "Text : " << it->second.getText() << std::endl;
    }
}

std::string NotesCollection::getName() const {
    return name;
}

void NotesCollection::setName(std::string n) {
    name = std::move(n);
}

void NotesCollection::printOneNotes(const std::string& noteTitle) {
    auto it = collection.find(noteTitle);
    if(it != collection.end()) {
        std::cout << "Title : " << it->first << std::endl;
        std::cout << "Text : " << it->second.getText() << std::endl;
    }
    else
        throw std::runtime_error("Note doesn't exist");
}

void NotesCollection::editNoteTitle(const std::string& oldTitle, std::string newTitle) {
    auto it = collection.find(oldTitle);
    if(it != collection.end()) {
        if(!(it->second.isBlocked()))
            it->second.setTitle(std::move(newTitle));
        else
            throw std::runtime_error("Note is blocked");
    }
    else
        throw std::runtime_error("Note doesn't exist");
}

void NotesCollection::editNoteText(const std::string& noteTitle, std::string newText) {
    auto it = collection.find(noteTitle);
    if(it != collection.end()) {
        if(!(it->second.isBlocked()))
            it->second.setText(std::move(newText));
        else
            throw std::runtime_error("Note is blocked");
    }
    else
        throw std::runtime_error("Note doesn't exist");
}

void NotesCollection::subscribe(Observer* o) {
    observers.push_back(o);
}

void NotesCollection::unsubscribe(Observer* o) {
    observers.remove(o);
}

void NotesCollection::notify() {
    for(auto it = observers.begin(); it != observers.end(); it++)
        (*it)->update();
}

void NotesCollection::block(const std::string& noteTitle) {
    auto it = collection.find(noteTitle);
    if(it != collection.end()) {
        if (!(it->second.isBlocked()))
            it->second.setBlocked(true);
        else
            throw std::runtime_error("Note is already blocked");
    }
    else
        throw std::runtime_error("Note doesn't exist");
}

void NotesCollection::unblock(const std::string& noteTitle) {
    auto it = collection.find(noteTitle);
    if(it != collection.end()) {
        if (it->second.isBlocked())
            it->second.setBlocked(false);
        else
            throw std::runtime_error("Note is already unblocked");
    }
    else
        throw std::runtime_error("Note doesn't exist");
}