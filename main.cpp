#include <iostream>
#include "Note.h"
#include "NotesCollection.h"
#include "App.h"

int main() {
    std::shared_ptr<Note> n1 = std::make_shared<Note>("n1", "t1");
    std::shared_ptr<Note> n2 = std::make_shared<Note>("n2", "t2");
    std::shared_ptr<Note> n3 = std::make_shared<Note>("n3", "t3");

    NotesCollection nc1("nc1");
    NotesCollection nc2("nc2");

    nc1.addNote(n1);
    nc1.addNote(n2);
    nc2.addNote(n1);
    nc2.addNote(n3);

    nc1.printAllNotes();
    nc2.printAllNotes();

    nc1.editNoteTitle(n1, "n1new");

    nc1.printAllNotes();
    nc2.printAllNotes();

    return 0;
}