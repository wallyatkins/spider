#ifndef CARDGROUP_H
#define CARDGROUP_H

#include <iostream>

#include "card.h"

class CardGroup
{
public:
	class OutOfRange {};
	class IllegalMove{};

	enum {MAX_SIZE = 208};

	CardGroup ()						{ howMany_ = 0; }
	CardGroup (const CardGroup& other)	{ *this = other; }
	CardGroup (const Card& other)		{ howMany_ = 0; addCard (other); }

	const CardGroup& operator= (const CardGroup&);
	bool operator== (const CardGroup&) const;
	bool operator!= (const CardGroup& other) const { return ! (*this == other); }

	Card& operator[] (unsigned int index);
	Card  operator[] (unsigned int index) const;
	bool outOfRange(int i) const { return i < 0 || i >= (int)size(); }
																	   
	Card	  top()		 const { return (*this)[size() - 1]; }
	CardGroup top(int i) const;
	Card	  remove			(unsigned int index);
	Card	  removeTop		()		 { return remove (size()-1);	}
	CardGroup removeTop(int start) { CardGroup result = top(start); discardAfter(start); return result; }
	void discardAfter(unsigned int newSize) { howMany_ = newSize;}

	unsigned int size   () const { return howMany_;				}
	bool		 isEmpty() const { return size() == 0;			}
	bool		 isFull () const { return size() >= MAX_SIZE;	}

	void addCard (const Card&); 

	void addCardLegally (const Card& other) 
	{ 
		if (isFull ()) throw IllegalMove();
		addCard (other); 
	}
	void addCardGroup(const CardGroup&);
	
	void print (std::ostream&) const;

private:
	unsigned int howMany_;
	Card contents_ [MAX_SIZE];
};

inline
std::ostream& operator<< (std::ostream& out, const CardGroup& foo)
{ 
	foo.print(out); return out; 
}

typedef CardGroup Hand;

#endif
