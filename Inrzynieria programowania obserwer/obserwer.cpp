#include"obserwer.h"
#include"person.h"


Observer::Observer(Person& person_to_observe, int number) : last_age(person_to_observe.get_age()) {

	link_to_data_pool = person_to_observe.get_my_data_pool();
	ID = number;

}


void Observer::run() {

	while (true)
	{
		this_thread::sleep_for(chrono::milliseconds(100));
		check_for_changes();

	}



}





void Observer::check_for_changes()
{
	
	int age = link_to_data_pool->get_age();
	if (last_age != age)
	{
		last_age = age;

		// Pobierz aktualny czas
		time_t now = std::time(nullptr);

		// Struktura do przechowywania zlokalizowanego czasu
		tm local_time;

		// U�yj localtime_s, aby przekonwertowa� czas na lokalny
		if (localtime_s(&local_time, &now) == 0) { // Sprawd�, czy funkcja si� powiod�a
			// Wy�wietl sformatowan� dat� i czas
			cout << ID << " change observed at : " << put_time(&local_time, "%Y-%m-%d %H:%M:%S") << " : " << last_age << endl;
		}
		else {
			std::cerr << "B��d podczas pobierania lokalnego czasu!" << std::endl;
		}




	}


}