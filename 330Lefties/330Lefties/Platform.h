#pragma once
#include "Unit.h"
#include "Sprite.h"
#include <iostream>

class Platform : public Unit
{
public:
	std::string currentseq = "";
	bool enablePhysics = true;
	//Platform();
	//~Platform();
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void handleEvent(Uint32 event) = 0;
};
