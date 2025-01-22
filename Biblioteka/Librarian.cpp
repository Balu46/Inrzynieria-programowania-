#include "Librarian.h"
#include "LibraryException.h"
#include "iostream"

Librarian::Librarian()
{

	server = Library::GetInstance();

}

Librarian::~Librarian()
{
}

Book* Librarian::boorw_book(std::string name)
{
	try
	{
		return server->borrow_book(name);
	}
	catch (LibraryException& e)
	{
		std::cout << "\n" << e.what() << "\n";
		throw e;
	}
	
}

Book* Librarian::subscribe_to_book(std::string name)
{
	try
	{
		return server->book_that_you_can_subscribe_to(name);
	}
	catch (LibraryException& e)
	{
		std::cout << "\n" << e.what() << "\n";
		throw e;
	}
}

void Librarian::return_book(int id_book)
{

	try
	{
		server->return_book(id_book);
	}
	catch (LibraryException& e)
	{
		std::cout << "\n" << e.what() << "\n";
		throw e;
	}

}

void Librarian::add_book_to_library(Book book)
{
	server->add_book_to_library(book);


}
