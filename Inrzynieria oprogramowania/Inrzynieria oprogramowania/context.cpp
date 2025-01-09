#include"context.h"
#include "state.h"
#include "State 1.h"

Context::Context(int what_state_number)  {
	
	list_of_states[0] = new ConcreteStateA;
	list_of_states[1] = new ConcreteStateB;

	list_of_states[0]->set_context(this);
	list_of_states[1]->set_context(this);

	this->setState(list_of_states[what_state_number]);

	
	
}
Context::Context() : curent_state(nullptr) {
	
	list_of_states[0] = new ConcreteStateA;
	list_of_states[1] = new ConcreteStateB;

	this->setState(this->list_of_states[0]);
}
void Context::Request1() {
	this->curent_state->Handle1();
}
void Context::Request2() {
	this->curent_state->Handle2();
}

void  Context::TransitionTo(int number_of_state) {

	this->setState(this->list_of_states[number_of_state]);


}