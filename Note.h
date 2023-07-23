//
// Created by filippo on 20/07/23.
//

#ifndef NOTES_NOTE_H
#define NOTES_NOTE_H

#include <iostream>
#include <utility>

class Note {
public:
    Note(std::string ti, std::string te, bool bl = false, bool im = false) : title(std::move(ti)), text(std::move(te)), blocked(bl), important(im) {}
    std::string getTitle() const;
    std::string getText() const;
    bool isBlocked() const;
    bool isImportant() const;
    void setTitle(std::string ti);
    void setText(std::string te);
    void setBlocked(bool bl);
    void setImportant(bool im);
private:
    std::string title, text;
    bool blocked, important;
};

#endif //NOTES_NOTE_H
