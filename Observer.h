//
// Created by filippo on 21/07/23.
//

#ifndef NOTES_OBSERVER_H
#define NOTES_OBSERVER_H

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update() = 0;
    virtual void attach() = 0;
    virtual void detach() = 0;

};

#endif //NOTES_OBSERVER_H
