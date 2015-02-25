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
}
