#pragma once
#include "context.h"



class State {
	/**
	* @var Context
	*/
protected:
	Context* context;

public:
	virtual ~State() {
	}

	void set_context(Context* context_) {
		this->context = context_;
	}

	virtual void Handle1() = 0;
	virtual void Handle2() = 0;

	State() : context() {

	}
};

/**
* The Context defines the interface of interest to clients. It also maintains a
* reference to an instance of a State subclass, which represents the current
* state of the Context.
*/

/**
* Concrete States implement various behaviors, associated with a state of the
* Context.
*/

