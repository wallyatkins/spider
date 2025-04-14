#include <iostream>

#include "card.h"

#include <cstdlib>

using namespace std;

inline int char2Int (char ch) { return ch - '0'; }

ostream& operator<< (ostream& out, Rank r)
{
	switch (r)
	{
		  case ACE: out << 'A'; break;
		 case JACK: out << 'J'; break;
		case QUEEN: out << 'Q'; break;
		 case KING: out << 'K'; break;
		   default: out << int (r);
	}
	return out;
}

istream& operator>> (istream& in, Rank& r)
{
	char answer;
	in >> answer;
	switch (toupper(answer))
	{
		case 'A': r = ACE;      break;
		case 'J': r = JACK;     break;
		case 'Q': r = QUEEN;    break;
		case 'K': r = KING;     break;
		default:
			if (isdigit(answer))
			{
				char second;
				in.get(second);
				if (isdigit(second))
				{
					string both; both += answer; both += second;
					int value = atoi(both.c_str());
					if (value == 10)
						r = Rank (10);
					else
						throw BadRankException();
				}
				else
				{
					if (answer == '1')
					{
						r = Rank (10);
						in.putback(second);
					}
					else
						r = Rank (char2Int(answer));
				}
			}
			else
				throw BadRankException();
	}
	return in;
}

ostream& operator<< (ostream& out, Suit s)
{
	switch (s)
	{
		case HEARTS  : out << 'H'; break;
		case DIAMONDS: out << 'D'; break;
		case CLUBS   : out << 'C'; break;
		case SPADES  : out << 'S'; break;
		default      : throw BadSuitException();
	}
	return out;
}

istream& operator>> (istream& in, Suit& s)
{
	char answer;
	in >> answer;
	switch (toupper(answer))
	{
		case 'H': s = HEARTS;   break;
		case 'D': s = DIAMONDS; break;
		case 'C': s = CLUBS;    break;
		case 'S': s = SPADES;   break;
		default : throw BadSuitException();
	}
	return in;
}

void Card::read (istream& in )
{
	try {	in  >> rank_  >> suit_;  }
	catch (BadRankException)	{	throw;	}
	catch (BadSuitException)	{	throw;	}
}
