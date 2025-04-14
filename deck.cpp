#include <cstdlib>
#include "deck.h"
#include <ctime>

using namespace std;

Deck::Deck() : CardGroup()
{
    for (int suit = 0; suit <= 3; suit++)
    {
        for (int value = 1; value <= 13; value++)
        {
            Card card = Card(Rank(value), Suit(suit));
            CardGroup::addCard(card);
        }
    }
}

bool Deck::isEmpty() const
{
    return CardGroup::isEmpty();
}

int Deck::size() const
{
    return CardGroup::size();
}

Card Deck::getCard(int index) const
{
    return CardGroup::operator[](index);
}

void Deck::shuffle()
{
    // Initialize the random seed if not already done
    static bool seeded = false;
    if (!seeded)
    {
        srand(static_cast<unsigned int>(time(nullptr)));
        seeded = true;
    }

    int deckSize = size();
    if (deckSize <= 1)
    {
        return;
    }

    for (int i = deckSize - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);

        Card temp = getCard(i);
        Card card_j = getCard(j);

        CardGroup::remove(i);
        CardGroup::remove(j < i ? j : j - 1);

        CardGroup::addCard(temp);
        CardGroup::addCard(card_j);
    }
}

Card Deck::deal()
{
    if (isEmpty())
    {
        return Card();
    }

    Card topCard = getCard(size() - 1);
    CardGroup::remove(size() - 1);
    return topCard;
}

Deck Deck::operator+(const Deck& other) const
{
    Deck result = *this;

    for (int i = 0; i < other.size(); i++)
    {
        result.CardGroup::addCard(other.getCard(i));
    }

    return result;
}
