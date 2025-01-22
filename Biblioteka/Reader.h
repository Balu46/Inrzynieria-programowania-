#pragma once
#include <list>
#include"Book.h"
#include"Librarian.h"
#include"iostream"

class Reader
{
public:
	Reader();
	~Reader();

	void borrow_book(std::string name);
	void return_book(std::string name);
	void subscribe_to_book(std::string name);

private:

	int user_id;
	std::list<Book*> Books_that_he_reads;
	Librarian* librarian;
	std::vector<Observer*> Books_i_am_subscribe_to;

};
