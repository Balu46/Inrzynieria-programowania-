#include"person.h"


void Person::changing_age() {

	

	srand(time(NULL));
	int number_of_random_changes = rand() % 50 + 10;

	for (int i = 0; i < number_of_random_changes; i++)
	{
		srand(time(NULL));
		this_thread::sleep_for(chrono::milliseconds(rand() % 2000 + 1000)); // i chose random time to wait before changing age

		srand(time(NULL));
		age = (rand() % 100 + 1); // i chose random age to change

		my_data->change_age(age);
		cout << endl << "I changed my age to : " << age << endl << endl;

	}


}

