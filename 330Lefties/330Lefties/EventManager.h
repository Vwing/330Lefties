#pragma once

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


