////
//// Uncomment this script and comment out main.cpp to see a sound demo 
////
//
//
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
//	SDL_Window *window = SDL_CreateWindow("Sound Demo", 800, 100, SCREEN_WIDTH,
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
//	const std::string resPath = getResourcePath("330LProject");
//
//	SDL_Texture *background = loadTexture(resPath + "background.png", renderer);
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
//	// The music that will be played
//	Sound *music = new Sound(resPath + "loop1.wav", false);
//
//	// Add a sound for walking to sprite1
//	Sound *walking = new Sound(resPath + "step1.wav");
//
//	SDL_Event e;
//	bool quit = false;
//	bool key_press = false;
//	std::string spriteDirection = "idle";
//	while (!quit){
//		// Play the music
//		music->play();
//
//		while (SDL_PollEvent(&e)){
//			if (e.type == SDL_QUIT){
//				quit = true;
//			}
//			if (e.type == SDL_KEYDOWN){
//				if (e.key.keysym.sym == SDLK_RIGHT)
//				{
//					// Play walking effect
//					walking->play();
//				}
//				else if (e.key.keysym.sym == SDLK_LEFT)
//				{
//					// Play walking effect
//					walking->play();
//				}
//				else if (e.key.keysym.sym == SDLK_UP)
//				{
//					// Play walking effect
//					walking->play();
//				}
//				else if (e.key.keysym.sym == SDLK_DOWN)
//				{
//					 //Play walking effect
//					walking->play();
//				}
//			}
//		}
//		// Render the scene
//		SDL_RenderClear(renderer);
//		spriteBG->show(bgFrame);
//		SDL_RenderPresent(renderer);
//	}
//
//	getchar();
//	cleanup(background, renderer, window);
//	Mix_Quit();  //Added Mix_Quit()
//	IMG_Quit();
//	SDL_Quit();
//
//	SDL_Quit();
//
//	return 0;
//}
