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
#include "SDL_mixer.h"
#include "SoundManager.h"

class Game : GameObject
{
public:
	Game(int windowWidth, int windowHeight, int xPos = 0, int yPos = 0);
	~Game();

	void update();
	void render();
	void handleEvent(Uint32 sdlEvent);

	void setEnvironment(int newWorldWidth, int newWorldHeight);

	bool isOver();
	void quitGame();

//	Sprite* addSprite(int width, int height, int xPos = 0, int yPos = 0);
	Sprite* createSprite(std::string resPath, int width, int height, int xPos = 0, int yPos = 0);
	Button* addButton(std::string resPath, Uint32 onDownEvent, int width, int height, int xPos = 0, int yPos = 0);
	Unit* addToEnvironment(Unit* gameObject);
	// Character* addCharacter(Sprite* sprite, int HP);  < This should be game programmer stuff

	SDL_Window *window;
	SDL_Renderer *renderer;

	Camera* camera; // Controls what gets seen in the environment
	Physics* physics;

private:

	// Window Dimensions
	int xPos, yPos;
	int windowHeight, windowWidth;
	bool quit;

	UI* ui;
	Environment *environment; // Contains all objects that are part of gameplay

};
