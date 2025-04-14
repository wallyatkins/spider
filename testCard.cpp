#include <iostream>
#include <cassert> 
#include "card.h"

using namespace std;

int main ()
{
	cout << "Enter 3 cards, using S for spades, H for hearts, etc.\n"
		 << "E.g. KS, 10H, 2C.  You can enter bogus ones like 12H or 5X.\n"
		 << "Use 0 for 10.\n";

	enum {INPUT_TRIALS = 3};
	for (int i = 0; i < INPUT_TRIALS; ++i)
	try 
	{
		Card inputCard;
		cout << "? ";
		cin  >> inputCard;
		cout << "You entered " << inputCard << endl;
	}
	catch (const BadRankException&)
	{
		cout << "The rank is invalid.\n";
	}
	
	catch (const BadSuitException&)
	{
		cout << "The suit is invalid; rank may be bad too.\n";
	}

	cout << "If there are no error messages below, "
	     << "it looks like class Card is working!\n";

	Card someCard, aceOfSpades(ACE, SPADES), copyOfAceOfSpades(aceOfSpades);

	assert (aceOfSpades == copyOfAceOfSpades);
	assert (someCard == Card (Rank(2), CLUBS));
	assert (someCard != aceOfSpades);
	someCard = aceOfSpades; 
	assert (someCard == aceOfSpades);
	assert (copyOfAceOfSpades.rank() == ACE && copyOfAceOfSpades.suit() == SPADES);
	assert (copyOfAceOfSpades.color() == BLACK);

	system ("pause");
}
