#include <memory>
#include "Note.h"
#include "NotesCollection.h"
#include "ImportantNotesCollection.h"
#include "App.h"

int main() {

    std::shared_ptr<Note> n1 = std::make_shared<Note>("n1", "text1");
    std::shared_ptr<Note> n2 = std::make_shared<Note>("n2", "text2");
    std::shared_ptr<Note> n3 = std::make_shared<Note>("n3", "text3");

    NotesCollection nc1("nc1");
    NotesCollection nc2("nc2");
    ImportantNotesCollection inc1("inc1");

    nc1.addNote(n1);
    nc1.addNote(n2);
    nc2.addNote(n1);
    nc2.addNote(n3);
    inc1.addImportantNote(n1);

    nc1.printAllNotes();
    nc2.printAllNotes();
    inc1.printAllImportantNotes();

    nc1.editNoteTitle(n1, "n1new");

    nc1.printAllNotes();
    nc2.printAllNotes();
    inc1.printAllImportantNotes();

    nc1.editNoteText(n1, "text1 new");

    nc1.printAllNotes();
    nc2.printAllNotes();
    inc1.printAllImportantNotes();

    nc1.removeNote(n1);

    nc1.printAllNotes();
    nc2.printAllNotes();
    inc1.printAllImportantNotes();

    inc1.removeImportantNote(n1);
    nc2.removeNote(n1);

    nc1.printAllNotes();
    nc2.printAllNotes();
    inc1.printAllImportantNotes();

    nc1.addNote(n1);
    nc2.addNote(n1);
    inc1.addImportantNote(n1);

    nc1.printAllNotes();
    nc2.printAllNotes();
    inc1.printAllImportantNotes();

    App app;
    app.attach(&nc1);
    app.attach(&nc2);
    app.attach(&inc1);

    app.update();

    app.detach(&nc1);
    app.detach(&nc2);
    app.detach(&inc1);

    app.update();

    return 0;
}