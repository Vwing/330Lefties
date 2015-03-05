#include <iostream>
#include <sstream>
#include <Windows.h>
#include <SDL.h>
#include "EventManager.h"
using namespace std;

std::string EventManager::Update(){
	cout << "Updating" << endl;
	SDL_Event e;
	bool receivedEvents = false;
	std::string eventString = "NoEvent!";
	while (SDL_PollEvent(&e)){
		cout << "Getting Events!" << endl;
		eventQueue.push(e);
		receivedEvents = true;
		if (receivedEvents)
			StartEventProcessing();// <-- TODO: make this actually process events after some time.
	}
	return eventString;
}

void EventManager::RegisterForEvent(Subscriber& subscriber, Uint32 theEvent){
	cout << "RegEvent: " << theEvent << endl;
	if (eventToListOfSubScribers.find(theEvent) == end(eventToListOfSubScribers)){//is there no list for this kind of event?
		cout << "New Event to listen for, so create a new list." << endl;
		SubscriberList newList;
		newList.push_back(subscriber);
		eventToListOfSubScribers.insert(std::pair<Uint32, SubscriberList>(theEvent, newList));
	}
	else{//seen this event before, so should have a list.
		cout << "Seen this event before, adding to already made list!" << endl;
		eventToListOfSubScribers[theEvent].push_back(subscriber);
	}
}

void EventManager::DispatchEvent(Uint32 theEvent){
	if (eventToListOfSubScribers.find(theEvent) != end(eventToListOfSubScribers)){//found the list
		SubscriberList listForThisEvent = eventToListOfSubScribers[theEvent];

		for (Subscriber s : listForThisEvent){
			cout << "trying to fire function for this event: " << s.eventID << endl;

			s.HandleRegisteredEvent(theEvent);
		}

	}
}

void EventManager::StartEventProcessing(){

	while (eventQueue.size() > 0){
		SDL_Event e = eventQueue.front();
		eventQueue.pop();//for some reason the pop doesn't return the element.

		//Try to get the right enum for this event
		Uint32 theEventEnum = e.type;//Start it by default as type
		if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP){//If its a Key press, get that key enum
			theEventEnum = e.key.keysym.sym;
			cout << "was a key!!!!!!!!!!!!!!" << endl;
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP){
			theEventEnum = e.button.button;//Left, Right
			cout << "Mouse click" << endl;
		}
		//else if (SDL_USEREVENT) <-- TODO!

		cout << "theEventEnum: " << theEventEnum << endl;
		DispatchEvent(theEventEnum);
	}
}



/*
#include <vector>
#include "SDL.h"
#include "GameObject.h"
#include "EventManager.h"


EventManager::~EventManager()
{
	eventQueue.clear();
	subscriberMap.clear();
}

void EventManager::updateQueue()
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		eventQueue.insert(eventQueue.begin(), e);
	}
}

void EventManager::subscribe(GameObject& const o, Uint32 eventType)
{
	std::map < Uint32, std::vector<GameObject* const>>::iterator it = subscriberMap.find(eventType);

	if (it == subscriberMap.end())
	{
		std::vector<GameObject* const> newSubscriberList;
		newSubscriberList.push_back(&o);

		subscriberMap.insert(std::pair<Uint32, std::vector<GameObject* const>>(eventType, newSubscriberList));
	}
	else
	{
		subscriberMap[eventType].push_back(&o);
	}
}

void EventManager::handleEvents()
{
	if (eventQueue.size() == 0)
	{
		return;
	}

	Uint32 start = SDL_GetTicks();

	while ((SDL_GetTicks() - start < timeToHandleEvents) && eventQueue.size() != 0)
	{
		SDL_Event e = eventQueue.back();

		std::map < Uint32, std::vector<GameObject* const>>::iterator it = subscriberMap.find(e.type);

		if (it != subscriberMap.end())
		{
			for (int i = 0; i < subscriberMap[e.type].size(); i++)
			{
				subscriberMap[e.type][i]->handleEvent(e);
			}
		}
		eventQueue.pop_back();
	}
}*/
