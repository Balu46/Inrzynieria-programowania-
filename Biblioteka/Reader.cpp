#include "Reader.h"
#include "LibraryException.h"

Reader::Reader()
{
	this->user_id = 0;
	librarian = new Librarian;
}

Reader::~Reader()
{
	delete librarian;
}

void Reader::borrow_book(std::string name)
{

	for (auto& book : this->Books_that_he_reads)
	{
		if (book->get_name() == name)
		{
			std::cout << "You try to borrow book that you alredy borrowed";

			return;
		}
	}

	Book* book_to_add = nullptr;

	try
	{
		book_to_add = this->librarian->boorw_book(name);
	}
	catch (LibraryException& e)
	{
		return;
	}


	this->Books_that_he_reads.push_back(book_to_add);
	
	

}

void Reader::return_book(std::string name)
{
	int id_book_to_return = -1;
	for (auto& book : Books_that_he_reads)
	{
		if (book->get_name() == name)
		{
			id_book_to_return = book->get_id();
		}
	}

	this->librarian->return_book(id_book_to_return);

	this->Books_that_he_reads.remove_if([&](Book* book) {
		
		return book->get_name() == name;
		
	});

		
	
	

}

void Reader::subscribe_to_book(std::string name)
{
	Book* b = librarian->subscribe_to_book(name);
	this->Books_i_am_subscribe_to.push_back(new Observer(*b)); 

}
