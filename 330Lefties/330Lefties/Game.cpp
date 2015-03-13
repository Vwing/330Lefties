#include <iostream>
#include "Game.h"
#include "SDL.h"
#include "Globals.h"
#include <SDL_image.h>

#include <cleanup.h>


Game::Game(int windowWidth, int windowHeight, int xPos, int yPos)
: windowWidth(windowWidth), windowHeight(windowHeight), xPos(xPos), yPos(yPos)
{
	quit = false;

	/*
		Load all of the SDL resources and set quit to true if there are any errors
	*/
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, SDL_GetError());
		quit = true;
	}

	// Initialize SDL_mixer
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, Mix_GetError());
		quit = true;
	}

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "IMG_Init");
		quit = true;
	}

	window = SDL_CreateWindow("Your Game", xPos, yPos, windowWidth,
		windowHeight, SDL_WINDOW_SHOWN);
	if (window == nullptr){
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Create Window Error");
		quit = true;
	}
	renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr){
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Create Renderer Error");
		quit = true;
	}

	/*	Environment will use window width and height as default
		NOTE: For a platformer game, the environment should be wider (and possibly
		higher than the window.
	*/
	environment = new Environment(windowWidth, windowHeight);
	camera = new Camera(windowWidth, windowHeight, environment);
	physics = new Physics(windowWidth, windowHeight);
	ui = new UI();

	Global_RegisterForEvent(this, SDLK_ESCAPE);
	Global_RegisterForEvent(this, SDL_WINDOWEVENT_CLOSE);
	Global_RegisterForEvent(this, SDL_QUIT);
	
}

Game::~Game()
{
	cleanup(window, renderer);
	delete environment, camera, physics;
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
}

void Game::update()
{
	EventManager::getInstance().Update();

	// Position the camera based on the current mode
	camera->update();
	// Call update on all environment objects
	environment->update();
	// Call update on all UI objects
	ui->update(); //TechDemo: had to comment out for tech demo to compile
}

void Game::render()
{
	SDL_RenderClear(renderer);

	// Render only what the camera can see.  
	// TO DO: Render things that are slightly off screen as well
	camera->render();
	
	// Render all UI Elements
	ui->render(); //TechDemo: Same as above update() method

	SDL_RenderPresent(renderer);
}

void Game::handleEvent(Uint32 sdlEvent)
{
	if (sdlEvent == SDLK_ESCAPE)
	{
		quit = true;
	}
}

void Game::setEnvironment(int newWorldWidth, int newWorldHeight)
{
	Environment* newEnv = new Environment(newWorldWidth, newWorldHeight);
	camera->setEnvironment(newEnv);
	physics->set_world(newEnv->getWidth(), newEnv->getHeight());
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
Sprite* Game::createSprite(std::string resPath, int width, int height, int xPos, int yPos)
{
	Sprite* newSprite = new Sprite(resPath, renderer, width, height, xPos, yPos);
	return newSprite;
}

Button* Game::addButton(std::string resPath, Uint32 onDownEvent, int width, int height, int xPos, int yPos)
{
	Sprite* buttonSprite = new Sprite(resPath, renderer, width, height, xPos, yPos, "BUTTON_UP");
	return ui->addButton(buttonSprite, onDownEvent);
}

Unit* Game::addToEnvironment(Unit* gameObject){
	environment->addObject(gameObject);
	return gameObject;
}


/*
Character* Game::addCharacter(Sprite* sprite, int HP){
	Character* newChar = new Character(sprite, renderer, HP);

	allGameObjects.push_back(newChar);
	environment->addObject(newChar);
	
	return newChar;
}
*/

bool Game::isOver()
{
	return quit;
}

void Game::quitGame()
{
	quit = true;
}

