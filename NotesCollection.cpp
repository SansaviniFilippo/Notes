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
    if(it != collection.end())
        collection.erase(it);
    else
        throw std::runtime_error("Note doesn't exist");
}