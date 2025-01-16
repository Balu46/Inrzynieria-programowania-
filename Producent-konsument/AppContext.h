#pragma once
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <vector>
#include "Consument.h"
#include "Producent.h"

class AppContext
{
public:
	AppContext();
	~AppContext();
	int app_functior();

private:

};





void consumerThread();

void producerThread();


