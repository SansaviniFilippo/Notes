#include <iostream>
#include "Note.h"
#include "NotesCollection.h"
#include "App.h"

int main() {
    Note note1("Note 1", "This is the first note.");
    Note note2("Note 2", "This is the second note.");
    Note note3("Note 3", "This is the third note.");

    NotesCollection collection1("My Collection");
    collection1.addNote(note1);
    collection1.addNote(note2);

    NotesCollection collection2("Work Collection");
    collection2.addNote(note3);

    App app;

    app.attach(&collection1);
    app.attach(&collection2);

    app.update();

    collection1.editNoteText("Note 1", "This is the updated text for Note 1.");

    collection2.removeNote("Note 3");


    app.detach(&collection2);

    Note note4("Note 4", "This is a new note.");
    collection1.addNote(note4);

    app.update();

    return 0;
}