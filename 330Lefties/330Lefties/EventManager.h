#pragma once

#include <iostream>
#include <sstream>

#include "SDL.h"
#include <vector>
#include <map>
#include <deque>
#include <queue>
#include "Subscriber.h"

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

	void RegisterForEvent(Subscriber& subscriber, Uint32 theEvent);
	void DispatchEvent(Uint32 theEvent);
	//static bool loadedOnce;
private:
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



/*#pragma once

#include "SDL.h"
#include <vector>
#include <map>
#include "GameObject.h"

class EventManager
{
public:
	static EventManager& getInstance()
	{
		static EventManager instance;
		return instance;
	}

	~EventManager();

	void updateQueue();
	void subscribe(GameObject& const o, Uint32 type);
	void handleEvents();

private:
	EventManager() {};

	EventManager(EventManager const &) = delete;
	void operator=(EventManager const&) = delete;

	// Time dedicated to handling events in handleEvents()
	int timeToHandleEvents = 100;
	std::vector<SDL_Event> eventQueue;
	std::map < Uint32, std::vector<GameObject* const>> subscriberMap;
};


*/