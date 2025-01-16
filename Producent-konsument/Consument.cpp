#include "Consument.h"

Consumer::Consumer()
{
}

Consumer::~Consumer()
{
}

void Consumer::consume_data()
{
    while (true) {


        Magazyn* magazyn = Magazyn::GetInstance(10); // geting instance of container to get data from

        MyStruct to_print = magazyn->removing_data(); // method of singleton to get data, and removing it form singleton

        std::cout << to_print.int1 << " "<< to_print.int2 << '\n'; // printing recived numbers form singleton
    }
}
