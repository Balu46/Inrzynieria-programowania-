#pragma once
#include <iostream>
#include <string>
#include "Components.h"
#include "Declarations.h"
/**
 * The Mediator interface declares a method used by components to notify the
 * mediator about various events. The Mediator may react to these events and
 * pass the execution to other components.
 */


class Mediator {
public:
    virtual void Notify(BaseComponent* sender, std::string event) const = 0;
};


/**
 * Concrete Mediators implement cooperative behavior by coordinating several
 * components.
 */
class ConcreteMediator : public Mediator {
private:
    Component1* component1_;
    Component2* component2_;

public:
    ConcreteMediator(Component1* c1, Component2* c2);

    void Notify(BaseComponent* sender, std::string event) const override;
};

