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
    void attach(std::unique_ptr<Subject> subject) override;
    void detach(std::unique_ptr<Subject> subject) override;
private:
    std::list<std::unique_ptr<Subject>> collections;
};

#endif //NOTES_APP_H
