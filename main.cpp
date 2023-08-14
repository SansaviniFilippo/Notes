#include <memory>
#include "Note.h"
#include "NotesCollection.h"
#include "ImportantNotesCollection.h"
#include "App.h"

int main() {

    NotesCollection c1("Notes Collection 1");
    NotesCollection c2("Notes Collection 2");
    ImportantNotesCollection iC("Important Notes Collection");

    App app;
    app.attach(&c1);
    app.attach(&c2);
    app.attach(&iC);

    std::shared_ptr<Note> n1 = std::make_shared<Note>("title 1", "text 1");
    std::shared_ptr<Note> n2 = std::make_shared<Note>("title 2", "text 2");
    std::shared_ptr<Note> n3 = std::make_shared<Note>("title 3", "text 3");

    std::cout << "Start" << std::endl;
    std::cout << "1 ----------" << std::endl;
    c1.addNote(n1);
    try {
        c1.addNote(n1);
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
    try {
        c2.addNote(n2);
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
    try {
        iC.addImportantNote(n1);
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << "2 ----------" << std::endl;
    c1.printAllNotesTitle();
    c2.printAllNotesTitle();
    iC.printAllImportantNotesTitle();

    std::cout << "3 ----------" << std::endl;
    c1.printAllNotes();
    c2.printAllNotes();
    iC.printAllImportantNotes();

    std::cout << "4 ----------" << std::endl;
    try {
        c1.editNoteTitle(n1, "new title 1");
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
    try {
        c2.editNoteText(n2, "new text 2");
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << "5 ----------" << std::endl;
    try {
        c1.printOneNotes(n1);
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
    try {
        c2.printOneNotes(n2);
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
    try {
        iC.printOneImportantNotes(n1);
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << "6 ----------" << std::endl;
    try {
        c1.addNote(n2);
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
    try {
        c1.addNote(n3);
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
    c1.printAllNotes();

    std::cout << "7 ----------" << std::endl;
    try {
        c1.removeNote(n1);
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
    c1.printAllNotes();
    c1.printAllRemovedNotes();

    std::cout << "8 ----------" << std::endl;
    try {
        c1.clearCollection();
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
    c1.printAllNotes();
    c1.printAllRemovedNotes();

    std::cout << "9 ----------" << std::endl;
    c2.printAllRemovedNotes();
    try {
        c2.emptyTheBin();
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
    c2.printAllRemovedNotes();

    std::cout << "10 ----------" << std::endl;
    try {
        iC.removeImportantNote(n1);
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
    iC.printAllRemovedImportantNotes();
    try {
        iC.emptyTheBinImportantNotes();
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
    iC.printAllRemovedImportantNotes();

    std::cout << "11 ----------" << std::endl;
    app.detach(&c1);
    app.detach(&c2);
    app.detach(&iC);
    std::cout << "Finish" << std::endl;

    return 0;
}