#ifndef SPIDER_H
#define SPIDER_H

#include <iostream>
#include "spiderPile.h"
#include "deck.h"

using namespace std;

class Spider
{
public:
	enum { NUMBER_OF_PILES          = 10};
	enum { CARDS_TO_DEAL_INITIALLY  = 54};

	Spider					();
	Spider					(const Spider&) = delete; 
	const Spider& operator= (const Spider&) = delete; 

	void play  ();

	void print (ostream&) const;

private:
	SpiderPile piles_ [NUMBER_OF_PILES];
	Deck deck_;

	bool isTimeToQuit_;

	void move ();
	void deal ();
	bool victory () const;

	void celebrate () const;

	bool allPilesNonempty() const;
};

inline
ostream& operator<< (ostream& out, const Spider& game)
{
	game.print(out); return out;
}
#endif
