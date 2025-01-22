#include "Library.h"
#include<algorithm>
#include"LibraryException.h"


/**
 * Static methods should be defined outside the class.
 */

Library* Library::pinstance_{ nullptr };
std::mutex Library::mutex_;

void Library::add_book_to_library(Book book_to_add)
{   
    const std::lock_guard<std::mutex> lock(mutex_);


    this->Books.push_back(book_to_add);

    this->Books.sort([](const Book& first, const Book& second) { 
        return first.get_name() < second.get_name();
    });

}

void Library::return_book(int id_book)
{
    const std::lock_guard<std::mutex> lock(mutex_);
    for (auto& book : this->Books)
    {
        if (book.get_id() == id_book)
        {
            
            if (book.get_status() == BORROWED)
            {
               

                book.set_status(AVAIBLE);
                std::cout << "Return this book :\nName : " << book.get_name() << "\nID : " << book.get_id() << "\n";
                return;
            }

        }
    }


    throw LibraryException("Library does not have that book");
}

Book Library::remove_book(std::string name)
{
    const std::lock_guard<std::mutex> lock(mutex_);

    for (auto& book : Books)
    {
        if (book.get_name() == name)
        {
          
            int id = book.get_id();
            std::remove(Books.begin(), Books.end(), id), Books.end();
            std::cout << "Removed this book :\nName : " << book.get_name() << "\nID : " << book.get_id() << "\n";
            return book;

        }
    }
    throw LibraryException("Library does not have that book");
}

Book* Library::borrow_book(std::string name)
{
    bool is_this_book_in_library = false;
    bool tried_to_borrowed_alredy_borrowed_book = false;
    const std::lock_guard<std::mutex> lock(mutex_);
   
    for (auto& book : this->Books)
    {
        if (book.get_name() == name)
        {
            if (book.get_status() == BORROWED)
            {
                tried_to_borrowed_alredy_borrowed_book = true;
            }
            else
            {
                is_this_book_in_library = true;
                book.set_status(BORROWED);

                std::cout << "Borrowed this book :\nName : " << book.get_name() << "\nID : " << book.get_id() << "\n";

                return &book;
            }
            
                 

        }
    }
    if (tried_to_borrowed_alredy_borrowed_book)
    {
        throw LibraryException("You tried to borrow borowed book");
    }
    if (is_this_book_in_library)
    {
        throw LibraryException("All books are borowed");
    }

    throw LibraryException("Library does not have that book"); 
}

Book* Library::book_that_you_can_subscribe_to(std::string name)
{
    const std::lock_guard<std::mutex> lock(mutex_);
    bool is_book_in_library = false;
    for (auto& book : this->Books)
    {
        if (book.get_name() == name)
        {
 
            is_book_in_library = true;
            if (book.get_status() == BORROWED)
            {
                std::cout << "Subscribed to this book :\nName : " << book.get_name() << "\nID : " << book.get_id() << "\n";
                return &book;
            }
         

        }
    }
    if (is_book_in_library)
    {
        throw LibraryException("All books are aviaible");
    }
    else
    {
        throw LibraryException("This book does not exist in library");
    }
}

/**
 * The first time we call GetInstance we will lock the storage location
 *      and then we make sure again that the variable is null and then we
 *      set the value. RU:
 */
Library* Library::GetInstance()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (pinstance_ == nullptr)
    {
        pinstance_ = new Library;
    }
    return pinstance_;
}

