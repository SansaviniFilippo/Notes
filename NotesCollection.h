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
    void removeNote(const Note& note);
    void editNoteTitle(const Note& note, std::string newTitle);
    void editNoteText(const Note& note, std::string newText);
    void printAllNotesTitle();
    void printAllNotes();
    void printOneNotes(const Note& note);
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
