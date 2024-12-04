#pragma once
#include <vector>
#include <thread>
#include"data_pool.h"
#include"person.h"
#include"obserwer.h"


int client() {

	cout << "observer book" << endl;

	data_pool* data = data_pool::GetInstance();

	Person p(10);
	thread person_thread(&Person::changing_age, &p);


	//vector<thread*> list_of_my_threads;



	Observer o1(p, 1);
	Observer o2(p, 2);
	Observer o3(p, 3);


	thread th1(&Observer::run, &o1);
	thread th2(&Observer::run, &o2);
	thread th3(&Observer::run, &o3);




	th1.join();
	th2.join();
	th3.join();

	person_thread.join();




	return 0;
}