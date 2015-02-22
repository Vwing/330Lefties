#pragma  once
#include<functional>
#include "SDL.h"
//void* is a way of saying anything can be passed.
// making a SubScriptionFunction type that takes in anything and returns void
typedef void(SubScriptionFunction(void* eventData));
//typedef void(*SubScriptionFunction)(void);
// making a CallingConditionFunction type that takes in a double and returns a bool
typedef bool(CallingConditionFunction(Uint32 eventID));

class Subscriber {
public:
	Subscriber();
	Subscriber(const Subscriber& copy);
	//Subscriber(void* owner);
	Subscriber(void* owner, Uint32 watchedEvent);
	//Subscriber(void* owner, Uint32 watchedEvent, void* callBack);
	Subscriber(Subscriber &other);

	void DefaultAction(void* data);
	bool DefaultCondition(Uint32 value);

	std::function<SubScriptionFunction> method;
	std::function<CallingConditionFunction> callingCondition;

	void* owner;
	double eventID;


};