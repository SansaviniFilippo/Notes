//
// Created by filippo on 21/07/23.
//

#ifndef NOTES_APP_H
#define NOTES_APP_H

#include "Observer.h"
#include "NotesCollection.h"
#include <memory>
#include <vector>

class App : public Observer {
public:
    ~App() override;
    void update() override;
    void attach(Subject* collection) override;
    void detach(Subject* collection) override;
private:
    std::vector<Subject*> collections;
};

#endif //NOTES_APP_H
