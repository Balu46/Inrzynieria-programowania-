#pragma once
#include <string>
#include <queue>
#include <vector>
#include <mutex>
#include <set>
#include <list>
#include <map>
#include "Book.h"


/**
 * The Library class defines the `GetInstance` method that serves as an
 * alternative to constructor and lets clients access the same instance of this
 * class over and over.
 */
class Library
{

    /**
     * The Library's constructor/destructor should always be private to
     * prevent direct construction/desctruction calls with the `new`/`delete`
     * operator.
     */
private:
    static Library* pinstance_;
    static std::mutex mutex_;

protected:
    Library() {}
    ~Library() {}


    std::list<Book> Books; // list contains book instance, number of book that library contains




public:
    /**
     * Librarys should not be cloneable.
     */
    Library(Library& other) = delete;
    /**
     * Librarys should not be assignable.
     */
    void operator=(const Library&) = delete;
    /**
     * This is the static method that controls the access to the Library
     * instance. On the first run, it creates a Library object and places it
     * into the static field. On subsequent runs, it returns the client existing
     * object stored in the static field.
     */

    static Library* GetInstance();


    void add_book_to_library(Book book_to_add);

    void return_book(int id_book);

    Book remove_book(std::string name);

    Book* borrow_book(std::string name);

    Book* book_that_you_can_subscribe_to(std::string name);



};

