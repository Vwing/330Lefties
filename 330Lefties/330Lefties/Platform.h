#pragma once
#include "Unit.h"
#include "Sprite.h"
#include <iostream>

class Platform : public Unit
{
public:

	bool enablePhysics = true;
	bool immovable = true;
	//Platform();
	//~Platform();
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void handleEvent(Uint32 sdlEvent) = 0;
};
