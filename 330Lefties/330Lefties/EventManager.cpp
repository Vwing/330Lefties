#include <iostream>
#include <sstream>
#include <Windows.h>
#include <SDL.h>
#include "EventManager.h"
using namespace std;

//void EventManager::Update(){
std::string EventManager::Update(){
	cout << "Updating" << endl;
	SDL_Event e;
	bool receivedEvents = false;
	std::string eventString = "NoEvent!";
	while (SDL_PollEvent(&e)){
		cout << "Getting Events!" << endl;
		eventQueue.push(e);
		receivedEvents = true;
		/*
		if (e.type == SDL_QUIT){
		quit = true;
		}
		if (e.type == SDL_KEYDOWN){
		if (e.key.keysym.sym == SDLK_RIGHT)
		{
		eventString = "walk right";
		}
		else if (e.key.keysym.sym == SDLK_LEFT)
		{
		eventString = "walk left";
		}
		else if (e.key.keysym.sym == SDLK_UP)
		{
		eventString = "walk up";
		}
		else if (e.key.keysym.sym == SDLK_DOWN)
		{
		eventString = "walk down";
		quit = true;
		}
		}
		*/
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
			//Wrapper_Int(&forwarder, &object);
			//Wrapper_Int(&s.DefaultAction, &s.owner);
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
