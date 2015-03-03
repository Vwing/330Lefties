#pragma once

#include "GameObject.h"
#include "SDL.h"

class Camera : public GameObject
{
public:
	Camera(int width, int height, int xPos = 0, int yPos = 0);

	bool canSee(GameObject* obj1); //stolen from Physics

	virtual void handleEvent(Uint32 sdlEvent);
	virtual void update();
	virtual void render();
};
