#include "Book.h"





int Observer::static_number_ = 0;

bool Book::operator==(const int other) const
{
	if (this->id_book == other)
	{
		return true;
	}
	else
	{
		return false;
	}
}
