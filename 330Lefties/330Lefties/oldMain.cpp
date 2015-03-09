//#include <iostream>
//#include <sstream>
//#include <Windows.h>
//#include <SDL.h>
//#include <res_path.h>
//#include <cleanup.h>
//#include <SDL_image.h>
//
//#include "Sprite.h"
//#include "EventManager.h"
//#include "Game.h"
//
//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;
//
///*
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
///*
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
//
//int main(int argc, char **argv){
//
//	/* 
//		All of the inits should be handled by the resource loading.
//		(SDL_Init , IMG_Init)
//	*/
//	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
//		std::ostringstream debugMsg;
//		debugMsg << "SDL_Init Error: " << SDL_GetError() << std::endl;
//		OutputDebugString(debugMsg.str().c_str());
//		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
//		return 1;
//	}
//
//	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
//		logSDLError(std::cout, "IMG_Init");
//		SDL_Quit();
//		return 1;
//	}
//
//	Game* game = new Game(SCREEN_WIDTH, SCREEN_HEIGHT, 500, 500);
//
//	const std::string resPath = getResourcePath("330LProject");
//	
//
//	SDL_Texture *background = loadTexture(resPath + "Background.png", game->renderer);
//	//Make sure all is well
//	if (background == nullptr){
//		cleanup(background);
//		IMG_Quit();
//		SDL_Quit();
//		return 1;
//	}
//
//	Sprite* spriteBG = game->addSprite(SCREEN_WIDTH, SCREEN_HEIGHT);
//	int bgFrame = spriteBG->makeFrame(background, 0, 0);
//
//	SDL_Texture *spritesheet = loadTexture(resPath + "newSpriteSheet.png", game->renderer);
//	if (spritesheet == nullptr){
//		cleanup(spritesheet);
//		IMG_Quit();
//		SDL_Quit();
//		return 1;
//	}
//
//	Sprite* sprite1 = game->addSprite(32, 32);
//
//	int down1 = sprite1->makeFrame(spritesheet, 0, 0);
//	int down2 = sprite1->makeFrame(spritesheet, 32, 0);
//	int down3 = sprite1->makeFrame(spritesheet, 64, 0);
//	int left1 = sprite1->makeFrame(spritesheet, 0, 32);
//	int left2 = sprite1->makeFrame(spritesheet, 32, 32);
//	int left3 = sprite1->makeFrame(spritesheet, 64, 32);
//	int right1 = sprite1->makeFrame(spritesheet, 0, 64);
//	int right2 = sprite1->makeFrame(spritesheet, 32, 64);
//	int right3 = sprite1->makeFrame(spritesheet, 64, 64);
//	int up1 = sprite1->makeFrame(spritesheet, 0, 96);
//	int up2 = sprite1->makeFrame(spritesheet, 32, 96);
//	int up3 = sprite1->makeFrame(spritesheet, 64, 96);
//
//	for (int i = 0; i < 6; i++)
//	{
//		sprite1->addFrameToSequence("walk down", down1);
//		sprite1->addFrameToSequence("walk left", left1);
//		sprite1->addFrameToSequence("walk right", right1);
//		sprite1->addFrameToSequence("walk up", up1);
//	}
//	for (int i = 0; i < 6; i++)
//	{
//		sprite1->addFrameToSequence("walk down", down2);
//		sprite1->addFrameToSequence("walk left", left2);
//		sprite1->addFrameToSequence("walk right", right2);
//		sprite1->addFrameToSequence("walk up", up2);
//	}
//	for (int i = 0; i < 6; i++)
//	{
//		sprite1->addFrameToSequence("walk down", down3);
//		sprite1->addFrameToSequence("walk left", left3);
//		sprite1->addFrameToSequence("walk right", right3);
//		sprite1->addFrameToSequence("walk up", up3);
//	}
//
//	int x = SCREEN_WIDTH / 2;
//	int y = SCREEN_HEIGHT / 2;
//	sprite1->setPos(x, y);
//
//	while (!game->isOver()){
//
//		game->update();
//		//Render the scene
//		game->render();
//	}
//
//	cleanup(background, spritesheet);
//	IMG_Quit();
//	SDL_Quit();
//
//	SDL_Quit();
//
//	getchar();
//
//	return 0;
//}
