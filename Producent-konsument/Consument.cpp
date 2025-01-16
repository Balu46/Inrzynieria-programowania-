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


        Magazyn* magazyn = Magazyn::GetInstance(10);

        MyStruct to_print = magazyn->removing_data();

        if (to_print.int1 == -1 && to_print.int2 == -1)
        {
            std::cout << "empty container" << "\n";
            continue;
        }
        std::cout << to_print.int1 << " "<< to_print.int2 << '\n';
    }
}
