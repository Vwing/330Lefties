#pragma once

#include "SDL.h"

class GameObject
{
public:

	struct Body
	{
		int xPos;
		int yPos;
		int width;
		int height;
		int layer = 1;
	};

	Body body;
	virtual void update() = 0;
	virtual void render() = 0;

	virtual void handleEvent(SDL_Event sdlEvent) = 0;
};
