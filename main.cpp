#include <memory>
#include "Note.h"
#include "NotesCollection.h"
#include "ImportantNotesCollection.h"
#include "App.h"

int main() {

    NotesCollection c1("Notes Collection 1");
    NotesCollection c2("Notes Collection 2");
    ImportantNotesCollection importantNotesCollection("Important Notes Collection");

    App app;
    app.attach(&c1);
    app.attach(&c2);
    app.attach(&importantNotesCollection);

    std::shared_ptr<Note> n1 = std::make_shared<Note>("title 1", "text 1");
    std::shared_ptr<Note> n2 = std::make_shared<Note>("title 2", "text 2");
    std::shared_ptr<Note> n3 = std::make_shared<Note>("title 3", "text 3");

    c1.addNote(n1);
    c1.addNote(n2);
    c2.addNote(n3);
    importantNotesCollection.addImportantNote(n1);

    c1.printAllNotes();
    c2.printAllNotes();
    importantNotesCollection.printAllImportantNotes();

    c1.editNoteTitle(n1, "title 1 new");

    c1.printAllNotes();
    c2.printAllNotes();
    importantNotesCollection.printAllImportantNotes();

    c1.editNoteText(n1, "text 1 new");

    c1.printAllNotes();
    c2.printAllNotes();
    importantNotesCollection.printAllImportantNotes();

    c1.removeNote(n1);
    c2.addNote(n1);
    importantNotesCollection.addImportantNote(n2);
    importantNotesCollection.removeImportantNote(n1);

    std::cout << "----------------------------------------------------------" << std::endl;
    c1.printAllNotes();
    c2.printAllNotes();
    importantNotesCollection.printAllImportantNotes();
    std::cout << "----------------------------------------------------------" << std::endl;
    c1.printAllRemovedNotesTitle();
    c2.printAllRemovedNotesTitle();
    importantNotesCollection.printAllRemovedImportantNotes();
    std::cout << "----------------------------------------------------------" << std::endl;



    app.detach(&c1);
    app.detach(&c2);
    app.detach(&importantNotesCollection);

    app.update();

    return 0;
}