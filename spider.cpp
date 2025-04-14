#include <string>
#include <iomanip>
#include "io.h"
#include "spider.h"

using namespace std;
	
enum {QUIT=-1, DEAL = -2};

bool inRange(int what, int lo, int hi) { return lo <= what && what <= hi; }

int myAtoi(char c) { if (inRange(c, '0', '9')) return c - '0'; else return 0; }

int spiderInput(const char* question, int min, int max, bool isDealAllowed)
{
	while (true)
	{
		char answer; cout << question; cin >> answer;
		int pile = myAtoi(answer);
		switch (toupper(answer))
		{
		case 'D': if (isDealAllowed && getYorNAnswer("Are you sure? ")) return DEAL; else break;
		case 'Q': if (getYorNAnswer("Are you sure? "))                  return QUIT; else break;
		default : if (inRange(pile, min, max))                          return pile; else break;
		}
	} 
}

Spider::Spider ()
{
	isTimeToQuit_ = false;

	deck_ = Deck() + Deck();
	deck_.shuffle();

	int whichPile = 0;
	for (int i = 0; i < CARDS_TO_DEAL_INITIALLY; ++i)
	{
		piles_[whichPile].addCard (deck_.deal());
		whichPile = (whichPile+1)%NUMBER_OF_PILES;
	}

	for (int i = 0; i < NUMBER_OF_PILES; ++i)
		piles_[i].turnTopCardUp();
}

void Spider::deal()
{
	for (int i = 0; i < NUMBER_OF_PILES; ++i)
		piles_[i].addCard(deck_.deal());
}

bool Spider::allPilesNonempty() const
{
	for (int i = 0; i < NUMBER_OF_PILES; ++i)
		if (piles_[i].isEmpty()) return false;

	return true;
}

void Spider::move ()
{
	int from, fromStart;

	const char* question = deck_.isEmpty() ?
		"Number of pile to move from, or (Q)uit: " :
		"Number of pile to move from, (D)eal, or (Q)uit: " ;

	switch (from = spiderInput(question, 0, NUMBER_OF_PILES, !deck_.isEmpty()))
	{
	case DEAL: if      (deck_.isEmpty    ()) cout << "No more cards available!\n";        
			   else if (!allPilesNonempty()) cout << "No piles can be empty on redeal.\n";
			   else                          deal();
			   return;
	case QUIT: isTimeToQuit_ = true;
			   return;
	}

	if (piles_[from].numFaceUp() == 1) 
		fromStart = piles_[from].size() - 1;
	else
	{
		cout << "Where in pile to start from, or (Q)uit: "; cin >> fromStart;
	}
	
	if (! piles_[from].isLegalToRemoveTop (fromStart))
	{
		cout << "You can't move from there; try again.\n\n"; return;
	}

	CardGroup thing = piles_[from].top(fromStart); 

	int to = spiderInput("Moving to: ", 0, NUMBER_OF_PILES,false);
	if (to == QUIT) { isTimeToQuit_ = true; return; }

	if (! piles_[to].isLegalToAdd (thing))
	{
		cout << "That's not a legal move; try again.\n"; return;
	}

	piles_[to].addCardGroup (piles_[from].removeTop (fromStart));
	piles_[to].removeCompleteSequenceIfPossible();
	if (piles_[from].firstFaceUp () >= piles_[from].size() || piles_[from].size()==1)
		piles_[from].turnTopCardUp();
}

void Spider::play ()
{
	while (true)
	{
		cout << *this << '\n';

		move();

		if (isTimeToQuit_) return;

		if (victory ())	{	celebrate(); return; }
	}
}

bool Spider::victory () const
{
	for (int p = 0; p < NUMBER_OF_PILES; ++p)
		if (! piles_[p].isEmpty()) return false;

	return true;
}

void Spider::celebrate () const
{
	cout << "*************************************************\n";
	cout << "**********   YOU ARE DA WINNER!  ****************\n";
	cout << "*************************************************\n";
}

void Spider::print (ostream& out) const
{
	out << "    Columns:\n";

	int biggestColumn = 0;
	for (int i = 0; i < NUMBER_OF_PILES; ++i)
		if (piles_[i].size() > biggestColumn) biggestColumn = piles_[i].size();

	out << "  ";
	for (int i = 0; i < biggestColumn; ++i)
		out << setw(3) << i << ' ';
	out << '\n';

	for (int i= 0; i < NUMBER_OF_PILES; ++i)
		out << i << ":  " << piles_[i] << "\n";
	
	out << "\n";
}
