#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <mutex>
#include <thread>
#include <chrono>
#include <random>
#include <ctime>
#include <iomanip>
#include"data_pool.h"
using namespace std;


class Observer
{
public:
	int last_age;
	int ID;
	data_pool* link_to_data_pool;


	void run();


	Observer(Person& person_to_observe, int number);

private:
	mutex sMutex;

	void check_for_changes(data_pool* source);
};
