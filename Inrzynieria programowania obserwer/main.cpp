#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <mutex>
#include <set>
#include <thread>
#include <chrono>
#include <random>
using namespace std;

#include <concurrent_vector.h>
using namespace Concurrency;

//#include <boost/thread/recursive_mutex.hpp>

//Dla tych co ich nie by�o na wyk�adzie z IO lub nie s�uchali to
// Stecz da� takie zadanie do zrobienia na za tydzie� :
//
//Trzeba zrobi� klas� Person, kt�ra b�dzie mia�a pole wiek.
// Ona ma sobie ten wiek zmienia� co jaki� losowy interwa�(m�wi�, �e w granicach 2 sekund) i
// wysy�a� t� informacj� do Singletona.
//
//Singleton ma s�u�y� jako data pool programu i mie� pola :
// wiek, std::vector<std::string>.
// W polu wiek ma przechowywa� wiek konkretnego obiektu typu Person.
//
//Ostatni� klas� jest observer, kt�ry co 100ms ma sprawdza� czy wiek przechowywany w singletonie si� zmieni�.
// Je�li tak, to do wektora w singletonie ma zapisa� loga w stylu : "Observer 2 zaobserwowa� zmian� o 10:00".
//



template<typename T> struct Observer;

template <typename T>
class Observable
{
public:
	typedef mutex mutex_t;

	void notify(T& source, const string& name)
	{
		vector<Observer<T>*> observers_copy;
		{
			lock_guard<mutex_t> lock{ mtx };
			observers_copy = observers;
		}
		for (auto obs : observers_copy)
			if (obs)
				obs->field_changed(source, name);

		observers.erase(
			remove(observers.begin(), observers.end(), nullptr),
			observers.end());
	}
	/*void notify(T& source, const string& name)
	{
		lock_guard<mutex_t> lock{ mtx };
		for (auto obs : observers)
			if (obs)
				obs->field_changed(source, name);

		observers.erase(
			remove(observers.begin(), observers.end(), nullptr),
			observers.end());
	}*/
	void subscribe(Observer<T>* f)
	{
		lock_guard<mutex_t> lock{ mtx };
		observers.push_back(f);
	}
	void unsubscribe(Observer<T>* o)
	{
		lock_guard<mutex_t> lock{ mtx };
		auto it = find(observers.begin(), observers.end(), o);
		if (it != observers.end())
			*it = nullptr; // cannot do this for a set
	}
private:
	vector<Observer<T>*> observers;
	mutex_t mtx;
};

template<typename T> class Observer
{
public:
	virtual void field_changed(T& source, const string& field_name) = 0;
};

class data_pool : Observable<data_pool>
{
public:


	data_pool(data_pool& other) = delete;
	void operator=(const data_pool&) = delete;
	static data_pool* GetInstance();
	void change_age(int age_to_change) {

		age = age_to_change;
	}

	data_pool() : age(0) {}
	~data_pool() {}

protected:

	int age;
	vector<string> comunicat;
	static data_pool* my_data;



private:

};

data_pool* data_pool::my_data = nullptr;;

/**
 * Static methods should be defined outside the class.
 */
data_pool* data_pool::GetInstance()
{
	/**
	 * This is a safer way to create an instance. instance = new Singleton is
	 * dangeruous in case two instance threads wants to access at the same time
	 */
	if (my_data == nullptr) {
		my_data = new data_pool;
	}
	return my_data;
}

class Person : public Observable<Person>
{
public:
	explicit Person(const int age)
		: age(age)
	{
	}


	void changing_age() {
		data_pool* my_data = data_pool::GetInstance();
		srand(time(NULL));
		int number_of_random_changes = rand() % 50 + 10	;
		for (int i = 0; i < number_of_random_changes; i++)
		{
			srand(time(NULL));
			this_thread::sleep_for(chrono::milliseconds(rand() % 2000 + 1000));
			srand(time(NULL));
			age = (rand() % 100 + 1);
			my_data->change_age(age);
			
		}

		
	}

	int get_age() const
	{
		return age;
	}
	  
	void set_age(const int age)
	{ 
		if (this->age == age) return;

		auto old_can_vote = can_vote();
		this->age = age;

		notify(*this, "age");

		if (old_can_vote != can_vote())
			notify(*this, "can_vote");
	}

	bool can_vote() const
	{
		return age >= 16;
	}
	
private:
	int age;
};

struct Creature
{
	
};

class ConsolePersonObserver : public Observer<Person>
{
public:
	void field_changed(Person& source, const string& field_name) override
	{
		cout << "Person's " << field_name << " has changed to "
			<< source.get_age() << ".\n";
	}
};

class TrafficAdministration : public Observer<Person>
{
public:
	void field_changed(	Person& source, const string& field_name) override
	{
		if (field_name == "age")
		{
			if (source.get_age() < 17)
				cout << "Whoa there, you are not old enough to drive!\n";
			else
			{
				// oh, ok, they are old enough, let's not monitor them anymore
				cout << "We no longer care!\n";
				source.unsubscribe(this);
			}
		}
	}
};

class Observing_in_100ms_intervals : public Observer<data_pool>
{
public:
	void field_changed(	Person& source, const string& field_name) override
	{
		if (field_name == "age")
		{
			if (source.get_age() < 17)
				cout << "Whoa there, you are not old enough to drive!\n";
			else
			{
				// oh, ok, they are old enough, let's not monitor them anymore
				cout << "We no longer care!\n";
				source.unsubscribe(this);
			}
		}
	}
};






int main()
{
	vector<thread> list_of_my_threads;

	//int n = 5;// emount of my threads;
	//for (int i = 0; i < n; i++)
	//{
	//	thread th;

	//	list_of_my_threads.push_back(th);
	//}

	cout << "observer book" << endl;

	/*Person p{ 20 };
	ConsolePersonObserver cpo;
	p.subscribe(&cpo);
	p.set_age(21);
	p.set_age(22);*/

	Person p{ 10 };
	TrafficAdministration o;
	p.subscribe(&o);
	p.set_age(16);
	p.set_age(17);
	p.set_age(21);
	
	getchar();
	return 0;
}