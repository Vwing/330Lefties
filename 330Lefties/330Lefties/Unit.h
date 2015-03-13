#pragma once

#include "GameObject.h"
#include "AI.h"

// 'Unit' objects are non-UI objects that can have AI or physics actions.
// They are stored in the environment
class Unit : public GameObject
{
public:

	bool enableAI = false;
	bool enablePhysics = false;
	AI* ai;
	
	void createAI()
	{
		if (enableAI)
		{
			ai = new AI(this->body.xPos, this->body.xPos);
		}
	}
	
	/*
	void createAI(Unit* u)
	{
		if (enableAI)
		{
			ai = new AI(u);
		}
	}
	*/
};
