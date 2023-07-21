//
// Created by filippo on 20/07/23.
//

#ifndef NOTES_NOTESCOLLECTION_H
#define NOTES_NOTESCOLLECTION_H


#include <iostream>
#include <map>
#include <utility>
#include <list>
#include "Note.h"
#include "Subject.h"

class NotesCollection : public Subject {
public:
    explicit NotesCollection(std::string n) : name(std::move(n)), noteNumber(0) {}
    void addNote(const Note& note);
    void removeNote(std::string noteTitle);
    void editNoteTitle(const std::string& oldTitle, std::string newTitle);
    void editNoteText(const std::string& noteTitle, std::string newText);
    void printAllNotesTitle();
    void printAllNotes();
    void printOneNotes(const std::string& noteTitle);
    void block(const std::string& noteTitle);
    void unblock(const std::string& noteTitle);
    std::string getName() const;
    void setName(std::string n);

    ~NotesCollection() override = default;
    void subscribe(Observer* o) override;
    void unsubscribe(Observer* o) override;
    void notify() override;
private:
    std::string name;
    std::map<std::string, Note> collection;
    std::list<Observer*> observers;
    int noteNumber;
};

#endif //NOTES_NOTESCOLLECTION_H
