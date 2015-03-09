#pragma once
#include "EventManager.h"
#include "GameObject.h"

static void Global_RegisterForEvent(GameObject* gameObject, Uint32 watchedEvent){
	Subscriber updateSubscriber(gameObject, watchedEvent);
	EventManager::getInstance().RegisterForEvent(updateSubscriber, watchedEvent);
}