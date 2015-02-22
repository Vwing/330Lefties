#pragma once
#include "EventManager.h"
//#include "GameObject.h"


static void Global_RegisterForEvent(Subscriber& subscriber, Uint32 watchedEvent){
	EventManager::getInstance().RegisterForEvent(subscriber, watchedEvent);
}

/*
void Wrapper_NoArgs(void(*fptr)(void*), void* context) {
fptr(context);
}

void Wrapper_Int(void(*fptr)(void*, int), void* context) {
fptr(context, 5);
}

void GameObject_MoveX_Forwarder(void* context, int x) {
static_cast<GameObject*>(context)->movex(x);
}*/



//typedef bool(CallingConditionFunction(Uint32 eventID));
//typedef void(Sprite::*)(void*nonused) spriteMemberNoArg;
/*
static void Global_RegisterForEvent(void* owner, Uint32 watchedEvent, void* callBack){
Subscriber subscriber(owner, watchedEvent, callBack);
EventManager::getInstance().RegisterForEvent(subscriber, watchedEvent);
}

static void Global_RegisterForEvent(void* owner, Uint32 watchedEvent, spriteMemberNoArg callBack){
Subscriber subscriber(owner, watchedEvent, callBack);
EventManager::getInstance().RegisterForEvent(subscriber, watchedEvent);
}
*/