#include"Librarian.h"
#include"Reader.h"
#include"Library.h"
#include <random>
#include <sstream>
#include <thread>
#include <chrono>	



void thread_function() {


	srand(time(NULL));
	int time = rand() & 100;

	std::this_thread::sleep_for(std::chrono::milliseconds(time));

	Reader r;

	int j = 0;

	for (int i = 0; i < 5; i++)
	{
		std::stringstream s;

		j = rand() % 5;

		s << "book" << j;

		r.borrow_book(s.str());

	}

	return;
}






int main() {




	std::vector<std::thread> Readers;

	Library* l = Library::GetInstance();




	for (int i = 0; i < 5; i++)
	{
		std::stringstream s;
		
		s << "book" << i;

		Book b;
		b.id_book = i;
		b.name = s.str();

		l->add_book_to_library(b);
	}





	for (int i = 0; i < 10; i++)
	{

		Readers.emplace_back(std::thread(thread_function));
	}


	for (auto& reader : Readers)
	{

		reader.join();
		
	}



	return 0;
}


