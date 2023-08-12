//
// Created by filippo on 20/07/23.
//

#ifndef NOTES_NOTESCOLLECTION_H
#define NOTES_NOTESCOLLECTION_H

#include <iostream>
#include <list>
#include "Note.h"
#include "Subject.h"

class NotesCollection : public Subject {
public:
    explicit NotesCollection(std::string n) : name(std::move(n)), noteNumber(0), removedNoteNumber(0) {}
    void addNote(std::shared_ptr<Note> note);
    void removeNote(const std::shared_ptr<Note>& note);
    void clearCollection();
    void editNoteTitle(const std::shared_ptr<Note>& note, std::string newTitle);
    void editNoteText(const std::shared_ptr<Note>& note, std::string newText);
    void printAllNotesTitle() const;
    void printAllNotes() const;
    void printOneNotes(const std::shared_ptr<Note>& note) const;
    void block(const std::shared_ptr<Note>& note);
    void unblock(const std::shared_ptr<Note>& note);
    void printAllRemovedNotesTitle() const;
    void printAllRemovedNotes() const;
    void emptyTheBin();
    std::string getName() const;
    void setName(std::string n);
    int getNoteNumber() const;
    int getRemovedNoteNumber() const;

    ~NotesCollection() override = default;
    void subscribe(Observer* o) override;
    void unsubscribe(Observer* o) override;
    void notify() override;
private:
    std::string name;
    std::list<std::shared_ptr<Note>> collection;
    std::list<std::shared_ptr<Note>> removedNotesCollection;
    std::list<Observer*> observers;
    int noteNumber, removedNoteNumber;

    void addRemovedNote(std::shared_ptr<Note> note);
    void removeRemovedNote(const std::shared_ptr<Note>& note);
};

#endif //NOTES_NOTESCOLLECTION_H