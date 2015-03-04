#pragma once

#include "SDL.h"
#include "EventManager.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Camera.h"
#include "Environment.h"
#include "Physics.h"
#include "Character.h"


class Game
{
public:
	Game(int windowWidth, int windowHeight, int xPos = 0, int yPos = 0);
	~Game();

	void update();
	void render();

	bool isOver();

//	Sprite* addSprite(int width, int height, int xPos = 0, int yPos = 0);
	Sprite* loadSprite(int width, int height, int xPos = 0, int yPos = 0, std::string filePath = "");
	GameObject* addGameObject(GameObject* gameObject);
	Character* addCharacter(Sprite* sprite, int HP);

	SDL_Window *window;
	SDL_Renderer *renderer;

private:

	// Window Dimensions
	int xPos, yPos;
	int windowHeight, windowWidth;
	bool quit;

	Environment *environment; // Contains all objects that are part of gameplay
	Camera *camera; // Not sure if needed here

	std::vector<GameObject*> allGameObjects;

};
