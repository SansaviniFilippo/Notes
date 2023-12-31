//
// Created by filippo on 23/07/23.
//

#ifndef NOTES_IMPORTANTNOTESCOLLECTION_H
#define NOTES_IMPORTANTNOTESCOLLECTION_H

#include <iostream>
#include <list>
#include "Note.h"
#include "Subject.h"

class ImportantNotesCollection : public Subject {
public:
    explicit ImportantNotesCollection(std::string n = "Important Notes Collection") : name(std::move(n)), noteNumber(0), removedNoteNumber(0) {}

    void addImportantNote(std::shared_ptr<Note> note);
    void removeImportantNote(const std::shared_ptr<Note>& note);
    void clearCollection();

    void printAllImportantNotesTitle() const;
    void printAllImportantNotes() const;
    void printOneImportantNotes(const std::shared_ptr<Note>& note) const;

    void printAllRemovedImportantNotesTitle() const;
    void printAllRemovedImportantNotes() const;
    void emptyTheBinImportantNotes();

    std::string getName() const;
    int getNoteNumber() const;
    int getRemovedNoteNumber() const;

    ~ImportantNotesCollection() override = default;
    void subscribe(Observer* o) override;
    void unsubscribe(Observer* o) override;
    void notify() override;
private:
    std::string name;
    std::list<std::shared_ptr<Note>> collection;
    std::list<std::shared_ptr<Note>> removedNotesCollection;
    std::list<Observer*> observers;
    int noteNumber, removedNoteNumber;

    void addRemovedImportantNotes(std::shared_ptr<Note> note);
    void removeRemovedImportantNotes(const std::shared_ptr<Note>& note);
};

#endif //NOTES_IMPORTANTNOTESCOLLECTION_H