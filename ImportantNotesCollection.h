//
// Created by filippo on 23/07/23.
//

#ifndef NOTES_IMPORTANTNOTESCOLLECTION_H
#define NOTES_IMPORTANTNOTESCOLLECTION_H

#include <iostream>
#include <map>
#include <utility>
#include <list>
#include "Note.h"
#include "Subject.h"

class ImportantNotesCollection : public Subject {
public:
    ImportantNotesCollection() : name("Important notes collection"), noteNumber(0) {}
    void addImportantNote(std::shared_ptr<Note> note);
    void removeImportantNote(std::shared_ptr<Note> note);
    void editImportantNoteTitle(std::shared_ptr<Note> note, std::string newTitle);
    void editImportantNoteText(std::shared_ptr<Note> note, std::string newText);
    void printAllImportantNotesTitle();
    void printAllImportantNotes();
    void printOneImportantNotes(std::shared_ptr<Note> note);
    void blockImportantNotes(std::shared_ptr<Note> note);
    void unblockImportantNotes(const std::shared_ptr<Note>& note);
    std::string getName() const;
    int getNoteNumber() const;

    ~ImportantNotesCollection() override = default;
    void subscribe(Observer* o) override;
    void unsubscribe(Observer* o) override;
    void notify() override;
private:
    std::string name;
    std::list<std::shared_ptr<Note>> collection;
    std::list<Observer*> observers;
    int noteNumber;
};

#endif //NOTES_IMPORTANTNOTESCOLLECTION_H
