//
// Created by filippo on 21/07/23.
//

#ifndef NOTES_APP_H
#define NOTES_APP_H

#include "Observer.h"
#include "NotesCollection.h"
#include "ImportantNotesCollection.h"

class App : public Observer {
public:
    App() : collectionsNumber(0) {}
    ~App() override = default;
    void update() override;
    void attach(Subject* subject) override;
    void detach(Subject* subject) override;
    int getCollectionsNumber() const;
private:
    std::list<Subject*> collections;
    int collectionsNumber;
};

#endif //NOTES_APP_H
