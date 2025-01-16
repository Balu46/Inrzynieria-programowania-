#include "Producent.h"

Producent::Producent()
{
}
Producent::~Producent()
{
}
int Producent::produceData()
{
    int randomNumber1 = rand() % 1000;
    int randomNumber2 = rand() % 1000;


    
    return 0;
}

void Producent::producer_thread()
{
    while (true) {
        

        Magazyn* magazyn = Magazyn::GetInstance(10);

        int randomNumber1 = rand() % 1000;
        int randomNumber2 = rand() % 1000;

        magazyn->adding_data(randomNumber1, randomNumber2);


    }
    
}


