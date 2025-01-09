//#include"Components.h"
//#include"mediator.h"
//#include "Declarations.h"
//
//BaseComponent::BaseComponent(Mediator* mediator = nullptr) : mediator_(mediator) {
//}
//void BaseComponent::set_mediator(Mediator* mediator) {
//    this->mediator_ = mediator;
//}
//
//


#include"Components.h"
#include"mediator.h"
#include "Declarations.h"

void Component2::DoC() {
    std::cout << "Component 2 does C.\n";
    this->mediator_->Notify(this, "C");
}
void Component2::DoD() {
    std::cout << "Component 2 does D.\n";
    this->mediator_->Notify(this, "D");
}



void Component1::DoA() {
    std::cout << "Component 1 does A.\n";
    this->mediator_->Notify(this, "A");
}
void Component1::DoB() {
    std::cout << "Component 1 does B.\n";
    this->mediator_->Notify(this, "B");
}