#pragma once
#include "mediator.h"
#include "Declarations.h"


/**
 * The Base Component provides the basic functionality of storing a mediator's
 * instance inside component objects.
 */



class BaseComponent {
protected:
    Mediator* mediator_;

public:
    BaseComponent(Mediator* mediator = nullptr) : mediator_(mediator) {
    }
    void set_mediator(Mediator* mediator) {
        this->mediator_ = mediator;
    }
};


class Component1 : public BaseComponent {
public:
    void DoA();
    void DoB();
};

class Component2 : public BaseComponent {
public:
    void DoC();
    void DoD();
};

