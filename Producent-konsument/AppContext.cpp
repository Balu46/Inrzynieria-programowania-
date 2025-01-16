#include "AppContext.h"

void consumerThread()
{
    Consumer co;
    co.consume_data();
}

void producerThread()
{
    Producent pr;
    pr.produceData();

}



AppContext::AppContext()
{
}

AppContext::~AppContext()
{
}

int AppContext::app_functior()
{

    std::vector<std::thread*> list_of_consumer; // list containing pointers to consumer threads
    std::vector<std::thread*> list_of_producers; // list containing pointers to producer threads

    int amout_of_consumers = 0;
    int amout_of_producers = 0;


    std::cout << "How many comsumers you want : ";
    std::cin >> amout_of_consumers;
    std::cout << "\n";

    std::cout << "How many producers you want : ";
    std::cin >> amout_of_producers;
    std::cout << "\n";
    
    for (int i = 0; i < amout_of_producers; i++)
    {
   
        list_of_producers.push_back(new std::thread(producerThread));

    }
    for (int i = 0; i < amout_of_consumers; i++)
    {
        list_of_consumer.push_back(new std::thread(consumerThread));

    }
        
    for (auto *i : list_of_consumer)
    {
        i->join();
    }


    for (auto *i : list_of_producers)
    {
        i->join();
    }




    return 0;
}

