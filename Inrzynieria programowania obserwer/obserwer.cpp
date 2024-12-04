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
		check_for_changes(link_to_data_pool);

	}



}





void Observer::check_for_changes(data_pool* source)
{
	std::lock_guard<std::mutex> lock(sMutex);

	if (last_age != source->get_age())
	{
		last_age = source->get_age();

		// Pobierz aktualny czas
		time_t now = std::time(nullptr);

		// Struktura do przechowywania zlokalizowanego czasu
		tm local_time;

		// U¿yj localtime_s, aby przekonwertowaæ czas na lokalny
		if (localtime_s(&local_time, &now) == 0) { // SprawdŸ, czy funkcja siê powiod³a
			// Wyœwietl sformatowan¹ datê i czas
			cout << ID << " change observed at : " << put_time(&local_time, "%Y-%m-%d %H:%M:%S") << " : " << last_age << endl;
		}
		else {
			std::cerr << "B³¹d podczas pobierania lokalnego czasu!" << std::endl;
		}




	}


}