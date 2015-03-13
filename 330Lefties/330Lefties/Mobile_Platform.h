#pragma once
#include "Platform.h"

class Mobile_Platform : public Platform
{
public:
	Mobile_Platform(Sprite* sp,std::string h);
	~Mobile_Platform();
	void update();
	void render();
	void handleEvent(Uint32 event);
private:
	int x;
	int y;
	Sprite* sprite;
	Uint32 timer;
	AI* ai;
};
