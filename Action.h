//
// Created by Daniel Naro on 4/10/2021.
//

#ifndef MUHLEALPHABETA_ACTION_H
#define MUHLEALPHABETA_ACTION_H


#include <cstdint>

class Action {
private:
    uint8_t from;
    uint8_t to;
    uint8_t eat;
public:
    Action(uint8_t from, uint8_t to, uint8_t eat);

    uint8_t getFrom() const;

    uint8_t getTo() const;

    uint8_t getEat() const;

    bool operator==(const Action &rhs) const;

    bool operator!=(const Action &rhs) const;

    bool operator<(const Action &rhs) const;

    bool operator>(const Action &rhs) const;

    bool operator<=(const Action &rhs) const;

    bool operator>=(const Action &rhs) const;
};


#endif //MUHLEALPHABETA_ACTION_H
