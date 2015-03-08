#pragma once

#include "SDL.h"
#include "EventManager.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Camera.h"
#include "Environment.h"
#include "Physics.h"
#include "Character.h"
#include "UI_Element.h"
#include "UI.h"

class Game
{
public:
	Game(int windowWidth, int windowHeight, int xPos = 0, int yPos = 0);
	~Game();

	void update();
	void render();

	bool isOver();

//	Sprite* addSprite(int width, int height, int xPos = 0, int yPos = 0);
	Sprite* createSprite(int width, int height, int xPos = 0, int yPos = 0);
	Unit* addToEnvironment(Unit* gameObject);
	// Character* addCharacter(Sprite* sprite, int HP);  < This should be game programmer stuff

	SDL_Window *window;
	SDL_Renderer *renderer;

	UI* UI;

private:

	// Window Dimensions
	int xPos, yPos;
	int windowHeight, windowWidth;
	bool quit;

	Environment *environment; // Contains all objects that are part of gameplay
	Camera *camera; // Controls what gets seen in the environment
};
