#pragma once

#include "SDL.h"
#include "EventManager.h"
#include "GameObject.h"
#include "Sprite.h"

class Game
{
public:
	Game(int windowWidth, int windowHeight, int xPos = 0, int yPos = 0);
	~Game();

	void update();
	void render();

	bool isOver();
	// void addObject(GameObject* o);

	Sprite* addSprite(int width, int height, int xPos = 0, int yPos = 0);
	
	SDL_Window *window;
	SDL_Renderer *renderer;

private:
	// Window Dimensions
	int xPos, yPos;
	int windowHeight, windowWidth;
	bool quit;

	std::vector<GameObject*> allGameObjects;

};
