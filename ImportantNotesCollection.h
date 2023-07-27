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
    explicit ImportantNotesCollection(std::string n = "Important Notes Collection") : name(std::move(n)), noteNumber(0) {}
    void addImportantNote(std::shared_ptr<Note> note);
    void removeImportantNote(const std::shared_ptr<Note>& note);
    void editImportantNoteTitle(const std::shared_ptr<Note>& note, std::string newTitle);
    void editImportantNoteText(const std::shared_ptr<Note>& note, std::string newText);
    void printAllImportantNotesTitle();
    void printAllImportantNotes();
    void printOneImportantNotes(const std::shared_ptr<Note>& note);
    void blockImportantNotes(const std::shared_ptr<Note>& note);
    void unblockImportantNotes(const std::shared_ptr<Note>& note);
    std::string getName() const;
    void setName(std::string n);
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