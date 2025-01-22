#pragma once
#include<algorithm>
#include"Library.h"

class Librarian
{
public:
	Librarian();
	~Librarian();

	Book* boorw_book(std::string name);


	Book* subscribe_to_book(std::string name);


	void return_book(int book_id);

	void add_book_to_library(Book book);





private:

	Library* server;


};

