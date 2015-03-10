#include <iostream>
#include <sstream>

#include "Subscriber.h"
Subscriber::Subscriber(){
	std::cout << "shouldn't be called" << std::endl;
}

Subscriber::Subscriber(const Subscriber& copy){
	this->owner = copy.owner;
	this->eventID = copy.eventID;

}

Subscriber::Subscriber(GameObject* owner, Uint32 watchedEvent){
	this->owner = owner;
	this->eventID = watchedEvent;
}

Subscriber::Subscriber(Subscriber &other){
	this->owner = other.owner;
	this->eventID = other.eventID;
}

void Subscriber::HandleRegisteredEvent(Uint32 e){
	owner->handleEvent(e);
}