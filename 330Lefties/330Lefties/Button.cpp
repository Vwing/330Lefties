#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <Windows.h>
#include <SDL.h>
#include "SDL_image.h"
#include "Button.h"
#include <windows.h>
#include <functional>
#include "Sprite.h"

Button::Button(SDL_Renderer* ren, std::string resPath, std::string spritesheet, std::function<void(void)> functocall, Sprite* sprite)
{
	this->renderer = ren;
	this->resPath = resPath;
	this->spritesheet = spritesheet;
	this->functocall = functocall;
	this->sprite = sprite;
}

void Button::logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
	std::ostringstream errMsg;
	errMsg << " error: " << SDL_GetError() << std::endl;
	OutputDebugString(errMsg.str().c_str());
}


SDL_Texture* Button::loadTexture(){
	const std::string file = resPath + spritesheet;
	SDL_Texture* texture = IMG_LoadTexture(renderer, file.c_str());
	if (texture == nullptr){
		logSDLError(std::cout, "LoadTexture");
	}
	return texture;
}


void Button::handleEvent(Uint32 sdlEvent){
	sprite->addFrameToSequence("mouse up", sprite->makeFrame(loadTexture(), 0, 0));
	sprite->addFrameToSequence("mouse down", sprite->makeFrame(loadTexture(), 0, body.height));
	std::string button = "mouse up";

	if (sdlEvent == SDL_MOUSEBUTTONUP || sdlEvent == SDL_MOUSEBUTTONDOWN || sdlEvent == SDL_MOUSEMOTION){
		int x, y;
		SDL_GetMouseState(&x, &y);
		bool inside = true;

		if (x < body.xPos || x > body.xPos + body.width || y < body.yPos || y > body.yPos + body.height)
			inside = false;
		if (!inside){
			button = "mouse up";
			sprite->show(button.c_str());
		}
		else{
			if (sdlEvent == SDL_MOUSEBUTTONUP){
				button = "mouse up";
				sprite->show(button.c_str());
			}
			else if (sdlEvent == SDL_MOUSEBUTTONDOWN){
				button = "mouse down";
				sprite->show(button.c_str());
				functocall();
			}
		}
	}
	sprite->show(button.c_str());

}
