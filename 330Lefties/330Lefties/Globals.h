#pragma once
#include "EventManager.h"
#include "GameObject.h"

static void Global_RegisterForEvent(GameObject* gameObject, Uint32 watchedEvent){
	Subscriber updateSubstirber(gameObject, watchedEvent);
	EventManager::getInstance().RegisterForEvent(updateSubstirber, watchedEvent);
}