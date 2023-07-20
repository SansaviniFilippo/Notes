//
// Created by filippo on 20/07/23.
//

#ifndef NOTES_NOTESCOLLECTION_H
#define NOTES_NOTESCOLLECTION_H


#include <iostream>
#include <map>
#include <utility>
#include "Note.h"

class NotesCollection {
public:
    NotesCollection(std::string n) : name(std::move(n)) {}
    void addNote(const Note& note);
    void removeNote(const Note& note);
    void printAllNotesTitle();
    void printAllNotes();
    std::string getName() const;
    void setName(std::string n);
private:
    std::string name;
    std::map<std::string, Note> collection;
};

#endif //NOTES_NOTESCOLLECTION_H
