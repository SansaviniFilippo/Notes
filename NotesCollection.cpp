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

void NotesCollection::removeNote(const Note& note) {
    auto it = collection.find(note.getTitle());
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

void NotesCollection::printOneNotes(const Note& note) {
    auto it = collection.find(note.getTitle());
    if(it != collection.end()) {
        std::cout << "Title : " << it->first << std::endl;
        std::cout << "Text : " << it->second.getText() << std::endl;
    }
    else
        throw std::runtime_error("Note doesn't exist");
}

void NotesCollection::editNoteTitle(const Note& note, std::string newTitle) {
    auto it = collection.find(note.getTitle());
    if(it != collection.end()) {
        if(!(it->second.isBlocked()))
            it->second.setTitle(std::move(newTitle));
        else
            throw std::runtime_error("Note is blocked");
    }
    else
        throw std::runtime_error("Note doesn't exist");
}

void NotesCollection::editNoteText(const Note& note, std::string newText) {
    auto it = collection.find(note.getTitle());
    if(it != collection.end()) {
        if(!(it->second.isBlocked()))
            it->second.setText(std::move(newText));
        else
            throw std::runtime_error("Note is blocked");
    }
    else
        throw std::runtime_error("Note doesn't exist");
}