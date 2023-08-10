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

    return 0;
}