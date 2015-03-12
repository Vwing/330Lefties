#pragma once

#include "SDL.h"
#include "Sound.h"
#include <string>
#include <map>

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
		int layer = 1;
		std::string tag; //a tag identifying the type of object
	};

	Body body; // Contains position and dimensions of object

	void setPos(int x, int y)
	{
		body.xPos = x;
		body.yPos = y;
	}

	virtual void update() = 0; // Updates the state of this game object - in main game loop
	virtual void render() = 0; // Draws this game object onto the renderer - in main game loop

	virtual void handleEvent(Uint32 sdlEvent) = 0; // Called by event manager if this object is subscribed to 'sdlEvent'
};
