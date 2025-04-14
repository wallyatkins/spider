#ifndef CARD_H
#define CARD_H
#include <iostream>

enum Rank {ACE=1, JACK=11, QUEEN, KING};
enum Suit {HEARTS, DIAMONDS, CLUBS, SPADES};
enum Color{BLACK, RED};

inline Rank operator++ (Rank& r)      { return r = Rank(int(r) + 1); }
inline Rank operator++ (Rank& r, int) { Rank old=r; ++r; return old;   }
inline Suit operator++ (Suit& s)      { return s = Suit(int(s) + 1); }
inline Suit operator++ (Suit& s, int) { Suit old=s; ++s; return old; }

std::ostream& operator<< (std::ostream& out, Rank r);
std::ostream& operator<< (std::ostream& out, Suit s);

std::istream& operator>> (std::istream& in, Rank &r);
std::istream& operator>> (std::istream& in, Suit &s);

class BadRankException {};
class BadSuitException {};

class Card
{
private:
	Suit suit_;
	Rank rank_;
public:
	Card (Rank r, Suit s) :	rank_(r), suit_(s) {}
	Card() : rank_(ACE), suit_(CLUBS) {}
	Card (const Card& other) : rank_(other.rank_), suit_(other.suit_) {}
	
	const Card& operator= (const Card& other)
	{
		rank_ = other.rank_;
		suit_ = other.suit_;
		return *this;
	}

	bool operator== (const Card& other) const
	{
		return rank_ == other.rank_ && suit_ == other.suit_;
	}
	bool operator!= (const Card& other) const
	{
		return !(*this == other);
	}

	Suit suit () const { return suit_; }
	Rank rank () const { return rank_; }
	Color color() const
	{
		if (suit()==HEARTS || suit() == DIAMONDS) return RED;
		else return BLACK;
	}

	void print (std::ostream &out) const { out << rank_ << suit_; }
	void read (std::istream &in );
};

inline std::ostream& operator<< (std::ostream& out, const Card& foo)
{
	foo.print (out); return out;
}

inline std::istream& operator>> (std::istream& in,        Card& foo)
{
	foo.read  (in);  return in;
}

#endif
