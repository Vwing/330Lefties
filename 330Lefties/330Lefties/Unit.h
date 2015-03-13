#pragma once

#include "GameObject.h"
#include "AI.h"

// 'Unit' objects are non-UI objects that can have AI or physics actions.
// They are stored in the environment
class Unit : public GameObject
{
public:
	AI* ai;
	bool enableAI = false;
	bool enablePhysics = false;

	AI* createAI(int x, int y)
	{
		if (enableAI)
		{
			ai = new AI(x, y);
			return ai;
		}
		return nullptr;
	}
};
