#include <iostream>
#include <sstream>

#include "Subscriber.h"
Subscriber::Subscriber(){
	std::cout << "shouldn't be called" << std::endl;
}

Subscriber::Subscriber(const Subscriber& copy){
	this->owner = copy.owner;
	this->callingCondition = copy.callingCondition;
	this->method = copy.method;
	this->eventID = copy.eventID;

}
/*
Subscriber::Subscriber(void* owner){
this->owner = owner;

callingCondition = std::bind(&Subscriber::DefaultCondition, this, 0);
method = std::bind(&Subscriber::DefaultAction, this, nullptr);
}*/

Subscriber::Subscriber(void* owner, Uint32 watchedEvent){
	this->owner = owner;
	this->eventID = watchedEvent;

	//callingCondition = std::bind(&SubScriber::DefaultCondition, this, 0.0);
	method = std::bind(&Subscriber::DefaultAction, this, nullptr);
}

/*
Subscriber::Subscriber(void* owner, Uint32 watchedEvent, void* callBack){
this->owner = owner;
this->eventID = watchedEvent;

//callingCondition = std::bind(&SubScriber::DefaultCondition, this, 0.0);
method = std::bind(callBack, this, nullptr);
}
*/
Subscriber::Subscriber(Subscriber &other){
	this->owner = other.owner;
	this->callingCondition = other.callingCondition;
	this->method = other.method;
	this->eventID = other.eventID;
}

void Subscriber::DefaultAction(void* data){
	std::cout << "Default Action!" << std::endl;
}

bool Subscriber::DefaultCondition(Uint32 value){
	return true;
}

