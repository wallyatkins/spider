#include "cardgroup.h"

using namespace std;

const CardGroup& CardGroup::operator= (const CardGroup& other)
{
	howMany_ = other.size ();

	for (unsigned int i = 0; i < size(); ++i)
		(*this)[i] = other[i];

	return *this;
}

bool CardGroup::operator== (const CardGroup& other) const
{
	if (size() != other.size()) return false;

	for (unsigned int i = 0; i < size(); ++i)
		if ((*this)[i] != other[i]) return false;

	return true;
}

Card& CardGroup::operator[] (unsigned int index)
{
	if ( (size_t)index >= size())
		throw out_of_range ("CardGroup::operator[]");

	return contents_[index];
}

Card  CardGroup::operator[] (unsigned int index) const
{
	if ( (size_t)index >= size()) 
		throw OutOfRange ();
	else 
		return contents_[index];
}

void CardGroup::addCard (const Card& c)
{
	if (isFull		 ( )) throw OutOfRange ();
	else contents_[howMany_++] = c;
}

Card CardGroup::remove    (unsigned int index)
{
	if (index >= size()) throw OutOfRange ();

	Card result = (*this) [index];

	for (unsigned int i = index; i < size()-1; ++i)  
		(*this)[i] = (*this)[i+1];

	--howMany_;

	return result;
}

void CardGroup::print (ostream& out) const
{
	if (isEmpty ()) 
		out << "---"; 
	else 
		for (unsigned int i = 0; i < size(); ++i) 
			out << (*this)[i] << ' ';
}

CardGroup CardGroup::top(int start) const
{
	CardGroup result;
	for (int i = start; i < (int) size(); ++i)
		result.addCard((*this)[i]);
	return result;
}

void CardGroup::addCardGroup(const CardGroup& other)
{
   for (unsigned int i = 0; i < other.size(); ++i) addCard(other[i]);
}
