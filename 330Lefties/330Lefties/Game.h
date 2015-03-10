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

class Game : GameObject
{
public:
	Game(int windowWidth, int windowHeight, int xPos = 0, int yPos = 0);
	~Game();

	void update();
	void render();
	void handleEvent(Uint32 sdlEvent);

	void setEnvironment(Environment *newEnv);

	bool isOver();
	void quitGame();

//	Sprite* addSprite(int width, int height, int xPos = 0, int yPos = 0);
	Sprite* createSprite(std::string resPath, int width, int height, int xPos = 0, int yPos = 0);
	Unit* addToEnvironment(Unit* gameObject);
	// Character* addCharacter(Sprite* sprite, int HP);  < This should be game programmer stuff

	SDL_Window *window;
	SDL_Renderer *renderer;

	UI* UI;
	Camera *camera; // Controls what gets seen in the environment

private:

	// Window Dimensions
	int xPos, yPos;
	int windowHeight, windowWidth;
	bool quit;

	Environment *environment; // Contains all objects that are part of gameplay

};
