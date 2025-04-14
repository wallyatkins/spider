#ifndef DECK_H
#define DECK_H

#include "cardgroup.h"

class Deck : private CardGroup
{
public:
    Deck();

    bool isEmpty() const;
    int size() const;
    Card getCard(int index) const;

    void shuffle();
    Card deal();

    Deck operator+(const Deck& other) const;
};

#endif