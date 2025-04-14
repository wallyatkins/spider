#ifndef SPIDERPILE_H
#define SPIDERPILE_H

#include <iostream>
#include "cardgroup.h"
#include <vector>

class SpiderPile : private CardGroup
{
public:
    SpiderPile();

    bool isEmpty() const;
    int size() const;
    Card getCard(int index) const;
    Card getTopCard() const;

    bool isCardFaceUp(int index) const;
    void setCardFaceUp(int index, bool faceUp);
    int numFaceUp() const;
    int firstFaceUp() const;
    void turnTopCardUp();

    void addCard(const Card& card);
    CardGroup removeTop(int start);
    bool isLegalToRemoveTop(int start) const;
    bool isLegalToAdd(const CardGroup& cards) const;
    void removeCompleteSequenceIfPossible();
    void addCardGroup(const CardGroup& cards);

    CardGroup top(int i) const;
    void print(std::ostream& out) const;
    friend std::ostream& operator<<(std::ostream& out, const SpiderPile& pile);

private:
    std::vector<bool> faceUp_;
};

#endif
