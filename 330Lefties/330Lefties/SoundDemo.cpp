//#include <iostream>
//#include <sstream>
//#include <Windows.h>
//#include <SDL.h>
//#include "SDL_mixer.h"
//#include "res_path.h"
//#include "cleanup.h"
//#include "SDL_image.h"
//#include "Sprite.h"
//#include "Sound.h"
//#include "SoundManager.h"
//
//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;
//
///**
//* Log an SDL error with some error message to the output stream of our choice
//* @param os The output stream to write the message to
//* @param msg The error message to write, format will be msg error: SDL_GetError()
//*/
//void logSDLError(std::ostream &os, const std::string &msg){
//	os << msg << " error: " << SDL_GetError() << std::endl;
//	std::ostringstream errMsg;
//	errMsg << " error: " << SDL_GetError() << std::endl;
//	OutputDebugString(errMsg.str().c_str());
//}
//
///**
//* Loads an image into a texture on the rendering device
//* @param file The image file to load
//* @param ren The renderer to load the texture onto
//* @return the loaded texture, or nullptr if something went wrong.
//*/
//SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren){
//	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
//	if (texture == nullptr){
//		logSDLError(std::cout, "LoadTexture");
//	}
//	return texture;
//}
//
//void initEverything()
//{
//	// Initialize SDL Everything
//	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
//		std::ostringstream debugMsg;
//		debugMsg << "SDL_Init Error: " << SDL_GetError() << std::endl;
//		OutputDebugString(debugMsg.str().c_str());
//		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
//		exit(1);
//	}
//
//	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
//		logSDLError(std::cout, "IMG_Init");
//		SDL_Quit();
//		exit(1);
//	}
//
//	// Initialize SDL_mixer
//	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
//	{
//		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
//		exit(1);
//	}
//}
//
//int main(int argc, char **argv){
//
//	initEverything();
//
//	SDL_Window *window = SDL_CreateWindow("Sprite Demo", 800, 100, SCREEN_WIDTH,
//		SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//	if (window == nullptr){
//		logSDLError(std::cout, "CreateWindow");
//		SDL_Quit();
//		return 1;
//	}
//	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
//		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//	if (renderer == nullptr){
//		logSDLError(std::cout, "CreateRenderer");
//		cleanup(window);
//		SDL_Quit();
//		return 1;
//	}
//
//	const std::string resPath = getResourcePath("SpriteDemo");
//
//	SDL_Texture *background = loadTexture(resPath + "grass.png", renderer);
//	// Make sure all is well
//	if (background == nullptr){
//		cleanup(background, renderer, window);
//		IMG_Quit();
//		SDL_Quit();
//		return 1;
//	}
//
//	Sprite* spriteBG = new Sprite(SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
//	spriteBG->setPos(0, 0);
//	int bgFrame = spriteBG->makeFrame(background, 0, 0);
//
//	SDL_Texture *spritesheet = loadTexture(resPath + "soldier.png", renderer);
//	// spritesheet is from "player.png" at www.briancollins1.com
//	if (spritesheet == nullptr){
//		cleanup(spritesheet, renderer, window);
//		IMG_Quit();
//		SDL_Quit();
//		return 1;
//	}
//
//	SDL_Texture *spritesheet2 = loadTexture(resPath + "Up.png", renderer);
//	if (spritesheet2 == nullptr){
//		cleanup(spritesheet2, renderer, window);
//		IMG_Quit();
//		SDL_Quit();
//		return 1;
//	}
//
//	SDL_Texture *spritesheet3 = loadTexture(resPath + "Down.png", renderer);
//	if (spritesheet3 == nullptr){
//		cleanup(spritesheet3, renderer, window);
//		IMG_Quit();
//		SDL_Quit();
//		return 1;
//	}
//
//	Sprite* sprite1 = new Sprite(64, 64, renderer);
//	sprite1->addFrameToSequence("idle", sprite1->makeFrame(spritesheet, 0, 128));
//
//	for (int i = 0; i<9; i++)
//	{
//		for (int j = 0; j<5; j++)
//		{
//			sprite1->addFrameToSequence("walk right", sprite1->makeFrame(spritesheet, i * 64, 192));
//		}
//	}
//
//	for (int i = 0; i<9; i++)
//	{
//		for (int j = 0; j<5; j++)
//		{
//			sprite1->addFrameToSequence("walk left", sprite1->makeFrame(spritesheet, i * 64, 64));
//		}
//	}
//
//	for (int i = 0; i<9; i++)
//	{
//		for (int j = 0; j<5; j++)
//		{
//			sprite1->addFrameToSequence("walk up", sprite1->makeFrame(spritesheet, i * 64, 0));
//		}
//	}
//
//	for (int i = 0; i<9; i++)
//	{
//		for (int j = 0; j<5; j++)
//		{
//			sprite1->addFrameToSequence("walk down", sprite1->makeFrame(spritesheet, i * 64, 128));
//		}
//	}
//
//	// Sound Stuff
//	
//	// Sound manager controls and stores all sounds
//	SoundManager *sounds = new SoundManager();
//
//	// Set the volume for the music
//	
//
//	// Set the backgound music
//	sounds->setMusic(resPath + "loop1.wav");
//
//	// Set the walking sound
//	sounds->createEffect("walk", resPath + "step1.wav");
//
//	// Set the jump sound
//	sounds->createEffect("jump", resPath + "jump.wav");
//
//
//
//	int x = SCREEN_WIDTH / 2;
//	int y = SCREEN_HEIGHT / 2;
//	sprite1->setPos(x, y);
//
//	SDL_Event e;
//	bool quit = false;
//	bool key_press = false;
//	std::string spriteDirection = "idle";
//	while (!quit){
//
//		while (SDL_PollEvent(&e)){
//			if (e.type == SDL_QUIT){
//				quit = true;
//			}
//
//			// Play background music
//			sounds->playMusic();
//
//			if (e.type == SDL_KEYDOWN){
//				if (e.key.keysym.sym == SDLK_SPACE)
//				{
//					// Play jump effect with space bar
//					sounds->playEffect("jump");
//				}
//				if (e.key.keysym.sym == SDLK_RIGHT)
//				{
//					// Play walking effect
//					sounds->playEffect("walk");
//
//					sprite1->movex(1);
//					spriteDirection = "walk right";
//				}
//				else if (e.key.keysym.sym == SDLK_LEFT)
//				{
//					// Pause the walking effect
//					sounds->pauseEffect("walk");
//
//					sprite1->movex(-1);
//					spriteDirection = "walk left";
//				}
//				else if (e.key.keysym.sym == SDLK_UP)
//				{
//					// Turns music volume up 1 level per call
//					sounds->musicVolUp();
//
//					sprite1->movey(-1);
//					spriteDirection = "walk up";
//				}
//				else if (e.key.keysym.sym == SDLK_DOWN)
//				{
//					// Turns music volume down 1 level per call
//					sounds->musicVolDown();
//
//					sprite1->movey(1);
//					spriteDirection = "walk down";
//				}
//			}
//		}
//		//Render the scene
//		SDL_RenderClear(renderer);
//		spriteBG->show(bgFrame);
//		sprite1->show(spriteDirection.c_str());
//		SDL_RenderPresent(renderer);
//	}
//
//	// Added these to free the sounds
//	//Mix_FreeMusic(music);
//	//music = NULL;
//
//	cleanup(background, spritesheet, spritesheet2, spritesheet3, renderer, window);
//	Mix_Quit();  //Added Mix_Quit()
//	IMG_Quit();
//	SDL_Quit();
//
//	return 0;
//}
