#include "Producent.h"

Producent::Producent()
{
}
Producent::~Producent()
{
}
int Producent::produceData()
{
    while (true) {


        Magazyn* magazyn = Magazyn::GetInstance(10);

        int randomNumber1 = rand() % 1000; // randomizie intiger to add to singletomm
        int randomNumber2 = rand() % 1000;

        magazyn->adding_data(randomNumber1, randomNumber2); // singleton metod for adding this number to singleton


    }
    
    return 0;
}



