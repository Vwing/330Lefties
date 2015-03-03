#include <iostream>
#include "Game.h"
#include "SDL.h"

Game::Game(int windowWidth, int windowHeight, int xPos, int yPos)
: windowWidth(windowWidth), windowHeight(windowHeight), xPos(xPos), yPos(yPos)
{
	quit = false;
	camera = new Camera(windowWidth, windowHeight);
	// Environment will use window width and height as default until we implement scrolling
	environment = new Environment(windowWidth, windowHeight, camera);

	// Load all resources
	window = SDL_CreateWindow("Your Game", xPos, yPos, windowWidth,
		windowHeight, SDL_WINDOW_SHOWN);
	if (window == nullptr){
		std::cout << "Create Window Error" << std::endl;
		SDL_Quit();
		// return 1;
	}
	renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr){
		std::cout << "Create Renderer Error" << std::endl;
		// cleanup(window);
		SDL_Quit();
		// return 1;
	}
}

Game::~Game()
{
	// cleanup(window, renderer);
}

void Game::update()
{
//	EventManager::getInstance().updateQueue();
	//EventManager::getInstance().handleEvents();
	EventManager::getInstance().Update();

	environment->update();

	for (GameObject* o : allGameObjects)
	{
		o->update();
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	for (GameObject* o : allGameObjects)
	{
		o->render();
	}
	SDL_RenderPresent(renderer);
}

/*
Sprite* Game::addSprite(int width, int height, int xPos, int yPos)
{
	Sprite* newSprite = new Sprite(width, height, renderer, xPos, yPos);

	allGameObjects.push_back(newSprite);
	environment->addObject(newSprite);

	return newSprite;
}
*/
Sprite* Game::loadSprite(int width, int height, int xPos, int yPos)
{
	Sprite* newSprite = new Sprite(width, height, renderer, xPos, yPos);
	return newSprite;
}

GameObject* Game::addGameObject(GameObject* gameObject){
	allGameObjects.push_back(gameObject);
	environment->addObject(gameObject);
	return gameObject;
}

Character* Game::addCharacter(Sprite* sprite, int HP){
	Character* newChar = new Character(sprite, renderer, HP);

	allGameObjects.push_back(newChar);
	environment->addObject(newChar);
	
	return newChar;
}

bool Game::isOver()
{
	return quit;
}
