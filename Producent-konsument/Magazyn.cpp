#include "Magazyn.h"


/**
 * Static methods should be defined outside the class.
 */

Magazyn* Magazyn::pinstance_{ nullptr };
std::mutex Magazyn::mutex_;

/**
 * The first time we call GetInstance we will lock the storage location
 *      and then we make sure again that the variable is null and then we
 *      set the value. RU:
 */
Magazyn* Magazyn::GetInstance(const int max_size_of_conteir)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (pinstance_ == nullptr)
    {
        pinstance_ = new Magazyn(max_size_of_conteir);
    }
    return pinstance_;
}

int Magazyn::adding_data(int first_int, int second_int)
{



    if (content_of_container.size() >= max_size)
    {
        space_to_add_data = false;
    }
 
    std::unique_lock <std::mutex> lock(mutex_);

    cv.wait(lock, [&]{ return space_to_add_data; });

    content_of_container.push({ first_int,second_int });

    does_conteiner_have_data = true;

    lock.unlock();
    cv.notify_all();

    return 1;


}

MyStruct Magazyn::removing_data()
{

    if (content_of_container.size() == 0)
    {
        does_conteiner_have_data = false;
    }

    std::unique_lock <std::mutex> lock(mutex_);

    cv.wait(lock, [&] { return does_conteiner_have_data; });

    MyStruct data_to_be_returned = content_of_container.front();
    content_of_container.pop();

    space_to_add_data = true;

    lock.unlock();
    cv.notify_all();

    return data_to_be_returned;
}
