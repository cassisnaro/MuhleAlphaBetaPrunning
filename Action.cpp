//
// Created by Daniel Naro on 4/10/2021.
//

#include "Action.h"

Action::Action(uint8_t from, uint8_t to, uint8_t eat) : from(from), to(to), eat(eat) {}

uint8_t Action::getFrom() const {
    return from;
}

uint8_t Action::getTo() const {
    return to;
}

uint8_t Action::getEat() const {
    return eat;
}

bool Action::operator==(const Action &rhs) const {
    return from == rhs.from &&
           to == rhs.to &&
           eat == rhs.eat;
}

bool Action::operator!=(const Action &rhs) const {
    return !(rhs == *this);
}

bool Action::operator<(const Action &rhs) const {
    if (from < rhs.from)
        return true;
    if (rhs.from < from)
        return false;
    if (to < rhs.to)
        return true;
    if (rhs.to < to)
        return false;
    return eat < rhs.eat;
}

bool Action::operator>(const Action &rhs) const {
    return rhs < *this;
}

bool Action::operator<=(const Action &rhs) const {
    return !(rhs < *this);
}

bool Action::operator>=(const Action &rhs) const {
    return !(*this < rhs);
}
