#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <mutex>
#include <thread>
#include <chrono>
#include <random>
#include <ctime>
using namespace std;

class data_pool
{
	friend class Person;

public:


	data_pool(data_pool& other) = delete;
	void operator=(const data_pool&) = delete;
	static data_pool* GetInstance();

	int get_age() {

		std::lock_guard<std::mutex> lock(sMutex);
		return age;
	}

	data_pool() : age(0) {}
	~data_pool() {}

protected:

	int age;
	vector<string> comunicat;
	static data_pool* my_data;



private:

	static std::mutex sMutex;

	void change_age(int age_to_change) {

		std::lock_guard<std::mutex> lock(sMutex);

		age = age_to_change;
	}


};

