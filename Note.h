//
// Created by filippo on 20/07/23.
//

#ifndef NOTES_NOTE_H
#define NOTES_NOTE_H

#include <iostream>
#include <utility>

class Note {
public:
    Note(std::string ti, std::string te, bool bl = false) : title(std::move(ti)), text(te), blocked(bl) {}
    std::string getTitle() const;
    std::string getText() const;
    bool isBlocked() const;
    void setTitle(std::string ti);
    void setText(std::string te);
    void setBlocked(bool bl);
private:
    std::string title, text;
    bool blocked;
};

#endif //NOTES_NOTE_H
