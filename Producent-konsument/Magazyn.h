#pragma once
#include <iostream>
#include <mutex>
#include <thread>
#include <queue>

struct MyStruct
{
    int int1;
    int int2;
};
/**
 * The Magazyn class defines the `GetInstance` method that serves as an
 * alternative to constructor and lets clients access the same instance of this
 * class over and over.
 */
class Magazyn
{

    /**
     * The Magazyn's constructor/destructor should always be private to
     * prevent direct construction/desctruction calls with the `new`/`delete`
     * operator.
     */
private:
    static Magazyn* pinstance_;
    static std::mutex mutex_;



protected:
    Magazyn(int max_size_of_conteir) : max_size(max_size_of_conteir)
    {
    }
    ~Magazyn() {}
    std::queue<MyStruct> content_of_container;
    int max_size;

public:
    /**
     * Magazyns should not be cloneable.
     */
    Magazyn(Magazyn& other) = delete;
    /**
     * Magazyns should not be assignable.
     */
    void operator=(const Magazyn&) = delete;
    /**
     * This is the static method that controls the access to the Magazyn
     * instance. On the first run, it creates a Magazyn object and places it
     * into the static field. On subsequent runs, it returns the client existing
     * object stored in the static field.
     */

    static Magazyn* GetInstance(const int max_size_of_conteir);
    /**
     * Finally, any Magazyn should define some business logic, which can be
     * executed on its instance.
     */

    int adding_data( int first_int ,int second_int);

    MyStruct removing_data();

    
};

