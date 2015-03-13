#pragma once
#include <iostream>
#include "Unit.h"
#include "Sprite.h"

class NPC : public Unit
{
public:
	bool enableAI = true;
	bool enablePhysics = true;

	//NPC();
	//~NPC();
	
	virtual void GameObject::update() = 0;
	virtual void GameObject::render() = 0;
	virtual void GameObject::handleEvent(Uint32 event) = 0;
};
