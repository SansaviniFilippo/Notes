//
// Created by filippo on 20/07/23.
//

#include "Note.h"

#include <utility>

std::string Note::getTitle() const {
    return title;
}

std::string Note::getText() const {
    return text;
}

bool Note::isBlocked() const {
    return blocked;
}

void Note::setTitle(std::string ti) {
    title = std::move(ti);
}

void Note::setText(std::string te) {
    text = std::move(te);
}

void Note::setBlocked(bool bl) {
    blocked = bl;
}