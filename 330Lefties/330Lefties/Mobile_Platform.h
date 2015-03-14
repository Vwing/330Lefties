#pragma once
#include "Platform.h"

class Mobile_Platform : public Platform
{
public:
	Mobile_Platform(Sprite* sp);
	~Mobile_Platform();
	void update();
	void render();
	void handleEvent(Uint32 event);
private:

	Sprite* sprite;
	Uint32 timer;
};
