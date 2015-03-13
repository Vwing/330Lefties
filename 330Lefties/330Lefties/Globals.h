#pragma once
#include "EventManager.h"
#include "GameObject.h"

enum userDefinedEvents{

	Collide = 1,
};

static void Global_RegisterForEvent(GameObject* gameObject, Uint32 watchedEvent){
	Subscriber updateSubscriber(gameObject, watchedEvent);
	EventManager::getInstance().RegisterForEvent(updateSubscriber, watchedEvent);
}

static void Global_FireEvent(userDefinedEvents firedEvent){
	EventManager::getInstance().DispatchEvent(firedEvent);
}