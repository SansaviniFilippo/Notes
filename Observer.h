//
// Created by filippo on 21/07/23.
//

#ifndef NOTES_OBSERVER_H
#define NOTES_OBSERVER_H

#include <iostream>
#include <memory>
#include "Subject.h"

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update() = 0;
    virtual void attach(Subject* subject) = 0;
    virtual void detach(Subject* subject) = 0;
};

#endif //NOTES_OBSERVER_H