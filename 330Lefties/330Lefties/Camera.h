#pragma once

#include "GameObject.h"

class Camera : public GameObject
{
public:
	Camera(int width = 500, int height = 500, int xPos = 0, int yPos = 0);

	bool canSee(GameObject* obj1); //stolen from Physics

	//SDL_Window *window;
	//SDL_Renderer *renderer;

	virtual void handleEvent(SDL_Event sdlEvent);
	virtual void update();
	virtual void render();
};