#pragma once

#include "SDL.h"

class GameObject
{
public:

	struct Body
	{
		int xPos;
		int yPos;
		int screenX;
		int screenY;
		int width;
		int height;
		bool physical = true; //does object use Physics
		float gravity = 1; //magnitude of gravity on object
		int layer = 1;
	};

	Body body;
	virtual void update() = 0;
	virtual void render() = 0;

	virtual void handleEvent(SDL_Event sdlEvent) = 0;
};
