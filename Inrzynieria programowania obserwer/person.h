#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <mutex>
#include <thread>
#include <chrono>
#include <random>
#include <ctime>
#include"data_pool.h"
using namespace std;






class Person
{
public:
	Person(const int age) : age(age)
	{

		my_data = data_pool::GetInstance();
	}


	void changing_age(); //function that changes persons age with random time in between to random age

	int get_age() const
	{
		return age;
	}

	data_pool* get_my_data_pool() { return my_data; }




protected:

private:
	data_pool* my_data; // link to my data_pool that is global singleton
	
	int age;
};



