#include "AppContext.h"

void consumerThread()
{
    Consumer co;
    co.consumer_theread();
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

    std::vector< std::thread> list_of_consumer;
    std::vector< std::thread> list_of_producers;

    std::thread t1(consumerThread);
    std::thread t2(producerThread);


    t1.join();
    t2.join();

    //for (int i = 0; i < 3; i++)
    //{
    //    std::thread t1(consumerThread);
    //    list_of_consumer.push_back(new );
    //}
    //for (int i = 0; i < 3; i++)
    //{
    //    std::thread t2(producerThread);
    //    list_of_producers.push_back(t2);
    //}


    //for (auto i : list_of_consumer )
    //{
    //    i.join();
    //}

    return 0;
}

