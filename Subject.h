//
// Created by filippo on 21/07/23.
//

#ifndef NOTES_SUBJECT_H
#define NOTES_SUBJECT_H

#include "Observer.h"

class Observer;

class Subject {
public:
    virtual void subscribe(Observer* o) = 0;
    virtual void unsubscribe(Observer* o) = 0;
    virtual void notify() = 0;
    virtual ~Subject() = default;
};

#endif //NOTES_SUBJECT_H