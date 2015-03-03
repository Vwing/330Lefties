#pragma  once
#include<functional>
#include "SDL.h"
#include "GameObject.h"

class Subscriber {
public:
	Subscriber();
	Subscriber(const Subscriber& copy);
	Subscriber(GameObject* owner, Uint32 watchedEvent);
	Subscriber(Subscriber &other);
	void HandleRegisteredEvent(SDL_Event e);
	void HandleRegisteredEvent(Uint32 e);
	GameObject* owner;
	Uint32 eventID;


};