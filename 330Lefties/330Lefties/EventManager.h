#pragma once

#include <iostream>
#include <sstream>

#include "SDL.h"
#include <vector>
#include <map>
#include <deque>
#include <queue>
#include "Subscriber.h"



//#include "Globals.h"

typedef std::vector<Subscriber> SubscriberList;
typedef std::map<Uint32, SubscriberList> MyMap;
class EventManager
{
public:
	//Necessary for a singleton!
	static EventManager& getInstance()
	{
		static EventManager instance; // Guaranteed to be destroyed.
		// Instantiated on first use.
		return instance;
	}

	std::string Update();

	//void RegisterForEvent(void* owner, std::string className, double eventToListenFor, SubScriptionFunction callBackFunction);
	void RegisterForEvent(Subscriber& subscriber, Uint32 theEvent);
	void DispatchEvent(Uint32 theEvent);
	//static bool loadedOnce;
private:
	//std::deque<SDL_Event> eventQueue;//deque because  supports more features like for each
	std::queue<SDL_Event> eventQueue;//deque because  supports more features like for each

	//Necessary for a singleton!
	EventManager(){};
	EventManager(EventManager const&) = delete;
	void operator=(EventManager const&) = delete;

	void StartEventProcessing();


	/*

	The eventToListOfSubScribers is a mapping of events to a list of all the Subscriptions for that Event.
	Each Subscription contains the reference to the class and function to call on this event.

	[SDLK_LEFT]->	[
	[&ClassA]	-> "OnSDLK_LEFT_FromClassA",
	[&ClassB]	-> "OnSDLK_LEFT_FromClassB",
	}

	*/
	MyMap eventToListOfSubScribers;

};

