//
// Created by filippo on 21/07/23.
//

#ifndef NOTES_APP_H
#define NOTES_APP_H

#include "Observer.h"
#include "NotesCollection.h"
#include <memory>
#include <map>

class App : public Observer {
public:
    ~App() override;
    void update() override;
    void attach(Subject* subject) override;
    void detach(Subject* subject) override;
private:
    std::map<std::string, Subject*> collections;
};

#endif //NOTES_APP_H
