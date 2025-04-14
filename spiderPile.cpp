#include "spiderPile.h"

#include <iostream>

SpiderPile::SpiderPile() : CardGroup()
{
    
}

bool SpiderPile::isEmpty() const
{
    return CardGroup::isEmpty();
}

int SpiderPile::size() const
{
    return CardGroup::size();
}

Card SpiderPile::getCard(int index) const
{
    return CardGroup::operator[](index);
}

Card SpiderPile::getTopCard() const
{
    if (isEmpty())
        return Card();

    return getCard(size() - 1);
}

bool SpiderPile::isCardFaceUp(int index) const
{
    if (index < 0 || index >= size() || index >= (int)faceUp_.size())
        return false;

    return faceUp_[index];
}

void SpiderPile::setCardFaceUp(int index, bool faceUp)
{
    if (index >= 0 && index < size())
    {
        if (index >= (int)faceUp_.size())
            faceUp_.resize(size(), false);

        faceUp_[index] = faceUp;
    }
}

int SpiderPile::numFaceUp() const
{
    int count = 0;
    for (int i = 0; i < size() && i < (int)faceUp_.size(); i++)
    {
        if (faceUp_[i])
            count++;
    }
    return count;
}

int SpiderPile::firstFaceUp() const
{
    for (int i = 0; i < size() && i < (int)faceUp_.size(); i++)
    {
        if (faceUp_[i])
            return i;
    }
    return size();
}

void SpiderPile::turnTopCardUp()
{
    // This function is called once per pile after the initial deal.
    // Since addCard now adds cards face-up, we need to turn all cards
    // face-down first, and then turn only the top card face-up to
    // achieve the correct initial state (all hidden except the last).
    if (!isEmpty())
    {
        int pileSize = size();
        // Ensure faceUp_ vector is the correct size and set all to false
        faceUp_.assign(pileSize, false); 
        // Set the top card face-up
        faceUp_[pileSize - 1] = true; 
    }
}

void SpiderPile::addCard(const Card& card)
{
    CardGroup::addCard(card);

    // Add cards face-up by default to handle the 'D' deal correctly.
    // The initial deal will be corrected by the modified turnTopCardUp.
    faceUp_.push_back(true);
}

CardGroup SpiderPile::removeTop(int start)
{
    CardGroup result;
    for (int i = start; i < size(); i++)
    {
        result.addCard(getCard(i));
    }

    int numToRemove = size() - start;
    for (int i = 0; i < numToRemove; i++)
    {
        CardGroup::remove(size() - 1);
        if (!faceUp_.empty())
            faceUp_.pop_back();
    }

    return result;
}

bool SpiderPile::isLegalToRemoveTop(int start) const
{
    int pileSize = size();

    if (start < 0 || start >= pileSize)
    {
        return false;
    }

    if (!isCardFaceUp(start))
    {
        return false;
    }

    Suit startSuit = getCard(start).suit();

    for (int i = start; i < pileSize - 1; i++)
    {
        if (!isCardFaceUp(i))
        {
            return false;
        }

        Card currentCard = getCard(i);
        Card nextCard = getCard(i + 1);

        if (nextCard.suit() != startSuit)
        {
            return false;
        }

        if (nextCard.rank() != currentCard.rank() - 1)
        {
            return false;
        }
    }

    return isCardFaceUp(pileSize - 1);
}

bool SpiderPile::isLegalToAdd(const CardGroup& cards) const
{
    if (cards.isEmpty())
        return true;

    if (isEmpty())
        return true;

    Card bottomOfSequence = cards[0];
    Card topOfPile = getTopCard();

    return (bottomOfSequence.rank() == topOfPile.rank() - 1);
}

void SpiderPile::removeCompleteSequenceIfPossible()
{
    int pileSize = size();

    if (pileSize < 13)
    {
        return;
    }

    if (getTopCard().rank() != ACE)
    {
        return;
    }

    int startIndex = pileSize - 13;
    Suit suit = getTopCard().suit();

    for (int i = 0; i < 13; i++)
    {
        int index = startIndex + i;
        Card card = getCard(index);

        if (!isCardFaceUp(index))
        {
            return;
        }

        if (card.suit() != suit)
        {
            return;
        }

        if (card.rank() != 13 - i)
        {
            return;
        }
    }

    removeTop(startIndex);

    if (!isEmpty())
    {
        turnTopCardUp();
    }
}

void SpiderPile::addCardGroup(const CardGroup& cards)
{
    for (int i = 0; i < cards.size(); i++)
    {
        Card card = cards[i];
        CardGroup::addCard(card);
        faceUp_.push_back(true);
    }
}

CardGroup SpiderPile::top(int i) const {
    return CardGroup::top(i);
}

void SpiderPile::print(std::ostream& out) const {
    CardGroup::print(out);
}

std::ostream& operator<<(std::ostream& out, const SpiderPile& pile) {
    if (pile.isEmpty()) {
        out << "..."; // Restore original empty pile format
    } else {
        out << ""; // Restore opening bracket
        for (int i = 0; i < pile.size(); ++i) {
            if (pile.isCardFaceUp(i)) {
                out << pile.getCard(i);
            } else {
                out << "XX";
            }
            if (i < pile.size() - 1) {
                out << " "; // Add space between cards
            }
        }
        out << ""; // Restore closing bracket
    }
    return out;
}
