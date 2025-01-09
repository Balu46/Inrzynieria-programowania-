#pragma once
#include <iostream>
#include <typeinfo>



class State;
/**
 * The Context defines the interface of interest to clients. It also maintains a
 * reference to an instance of a State subclass, which represents the current
 * state of the Context.
 */

class Context {
	/**
	* @var State A reference to the current state of the Context.
	*/
private:
	State* curent_state;
	State* list_of_states[2];
	bool is_actual;

public:
	State* getState(void) { return curent_state; }
	void setState(State* state) { curent_state = state; }

	void TransitionTo( int number_of_state);

	Context(int what_state_number);
	Context();

	~Context() {
		delete curent_state;
	}

	
	void Request1();
	void Request2();
};

