#include <iostream>
#include "Game.h"
#include "SDL.h"

Game::Game(int windowWidth, int windowHeight, int xPos, int yPos)
:windowHeight(windowHeight), windowWidth(windowWidth), xPos(xPos), yPos(yPos)
{
	quit = false;

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
	EventManager::getInstance().updateQueue();
	EventManager::getInstance().handleEvents();

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

Sprite* Game::addSprite(int width, int height, int xPos, int yPos)
{
	Sprite* newSprite = new Sprite(width, height, renderer, xPos, yPos);

	allGameObjects.push_back(newSprite);

	return newSprite;
}

bool Game::isOver()
{
	return quit;
}
