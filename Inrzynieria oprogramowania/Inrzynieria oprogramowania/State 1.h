#include"STATE.H"


class ConcreteStateA : public State {
public:

	void Handle1() override
	{
		std::cout << "ConcreteStateA handles request1.\n";
		std::cout << "ConcreteStateA wants to change the state of the context.\n";

		this->context->TransitionTo(1);
	}

	void Handle2() override {
		std::cout << "ConcreteStateA handles request2.\n";
	}

	void setActStateA() {


		std::cout << "jestem" << "1" << "/n";
	}

};

class ConcreteStateB : public State {
public:
	void Handle1() override {
		std::cout << "ConcreteStateB handles request1.\n";
	}
	void Handle2() override {
		std::cout << "ConcreteStateB handles request2.\n";
		std::cout << "ConcreteStateB wants to change the state of the context.\n";
		this->context->TransitionTo(0);
	}

	void setActStateA() {


		std::cout << "jestem" << "2" << "/n";
	}

};

