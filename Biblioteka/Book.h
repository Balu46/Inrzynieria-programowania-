#pragma once
#include <string>


enum book_staus
{
	BORROWED,
	AVAIBLE
	
};



/**
 * Observer Design Pattern
 *
 * Intent: Lets you define a subscription mechanism to notify multiple objects
 * about any events that happen to the object they're observing.
 *
 * Note that there's a lot of different terms with similar meaning associated
 * with this pattern. Just remember that the Subject is also called the
 * Publisher and the Observer is often called the Subscriber and vice versa.
 * Also the verbs "observe", "listen" or "track" usually mean the same thing.
 */

#include <iostream>
#include <list>
#include <string>

class IObserver {
public:
    virtual ~IObserver() {};
    virtual void Update(const std::string& message_from_subject) = 0;
};

class ISubject {
public:
    virtual ~ISubject() {};
    virtual void Attach(IObserver* observer) = 0;
    virtual void Detach(IObserver* observer) = 0;
    virtual void Notify() = 0;
};

/**
 * The Subject owns some important state and notifies observers when the state
 * changes.
 */

class Book : public ISubject {
public:

    Book() {
        this->id_book = -1;
        this->status = AVAIBLE;

    }
    virtual ~Book() {

    }

    /**
     * The subscription management methods.
     */
    void Attach(IObserver* observer) override {
        list_observer_.push_back(observer);
    }
    void Detach(IObserver* observer) override {
        list_observer_.remove(observer);
    }
    void Notify() override {
        std::list<IObserver*>::iterator iterator = list_observer_.begin();
        HowManyObserver();
        while (iterator != list_observer_.end()) {
            (*iterator)->Update(message_);
            ++iterator;
        }
    }

    void CreateMessage(std::string message = "Empty") {
        this->message_ = message;
        Notify();
    }
    void HowManyObserver() {
        std::cout << "There are " << list_observer_.size() << " observers in the list.\n";
    }

    /**
     * Usually, the subscription logic is only a fraction of what a Subject can
     * really do. Subjects commonly hold some important business logic, that
     * triggers a notification method whenever something important is about to
     * happen (or after it).
     */
    //void SomeBusinessLogic() {
    //    this->message_ = "change message message";
    //    Notify();
    //    std::cout << "I'm about to do some thing important\n";
    //}


    bool operator==(const int other) const;



    std::string get_name() const { return name; };
    int get_status() const { return status; }
    int get_id() const { return id_book; }

    void set_status(int status_to_set) { 
        int status_befor_change = status;
        status = status_to_set;
        if (status == AVAIBLE && status_befor_change == BORROWED)
        {
            Notify();
        }
    }


    friend int main();

private:
    std::list<IObserver*> list_observer_;
    std::string message_;

    int id_book;
    std::string name;
    int status;


};

class Observer : public IObserver {
public:
    Observer(Book& subject) : subject_(subject) {
        this->subject_.Attach(this);
        std::cout << "Hi, I'm the Observer \"" << ++Observer::static_number_ << "\".\n";
        this->number_ = Observer::static_number_;
    }
    virtual ~Observer() {
        std::cout << "Goodbye, I was the Observer \"" << this->number_ << "\".\n";
    }

    void Update(const std::string& message_from_subject) override {
        message_from_subject_ = message_from_subject;
        PrintInfo();
    }
    void RemoveMeFromTheList() {
        subject_.Detach(this);
        std::cout << "Observer \"" << number_ << "\" removed from the list.\n";
    }
    void PrintInfo() {
        std::cout << "Observer \"" << this->number_ << "\": a new message is available --> " << this->message_from_subject_ << "\n";
    }

private:
    std::string message_from_subject_;
    Book& subject_;
    static int static_number_;
    int number_;
};


//void ClientCode() {
//    Book* subject = new Book;
//    Observer* observer1 = new Observer(*subject);
//    Observer* observer2 = new Observer(*subject);
//    Observer* observer3 = new Observer(*subject);
//    Observer* observer4;
//    Observer* observer5;
//
//    subject->CreateMessage("Hello World! :D");
//    observer3->RemoveMeFromTheList();
//
//    subject->CreateMessage("The weather is hot today! :p");
//    observer4 = new Observer(*subject);
//
//    observer2->RemoveMeFromTheList();
//    observer5 = new Observer(*subject);
//
//    subject->CreateMessage("My new car is great! ;)");
//    observer5->RemoveMeFromTheList();
//
//    observer4->RemoveMeFromTheList();
//    observer1->RemoveMeFromTheList();
//
//    delete observer5;
//    delete observer4;
//    delete observer3;
//    delete observer2;
//    delete observer1;
//    delete subject;
//}
//    