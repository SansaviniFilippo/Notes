//
// Created by filippo on 21/07/23.
//

#ifndef NOTES_APP_H
#define NOTES_APP_H

#include "Observer.h"
#include "NotesCollection.h"
#include <memory>

class App : public Observer {
public:
    explicit App(std::unique_ptr<NotesCollection> s);
    ~App() override;
    void update() override;
    void attach() override;
    void detach() override;
private:
    std::unique_ptr<NotesCollection> subject;
};

#endif //NOTES_APP_H
