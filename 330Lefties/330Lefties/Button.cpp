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


Button::Button(std::function<void(void)> functocall, Sprite* sprite)
{
	this->functocall = functocall;
	this->sprite = sprite;
}

void Button::onButtonDown(int frameNum){
	press.buttonDown = frameNum;
}
void Button::onButtonUp(int frameNum){
	press.buttonUp = frameNum;
}
void Button::onButtonOver(int frameNum){
	press.buttonOver = frameNum;
}

int Button::getButtonDown(){
	return press.buttonDown;
}
int Button::getButtonUp(){
	return press.buttonUp;
}
int Button::getButtonOver(){
	return press.buttonOver;
}

void Button::handleEvent(Uint32 sdlEvent){
	if (sdlEvent == SDL_MOUSEBUTTONUP || sdlEvent == SDL_MOUSEBUTTONDOWN || sdlEvent == SDL_MOUSEMOTION){
		int x, y;
		SDL_GetMouseState(&x, &y);
		bool inside = true;

		if (x < body.xPos || x > body.xPos + body.width || y < body.yPos || y > body.yPos + body.height)
			inside = false;
		if (!inside){
			sprite->show(getButtonUp());
		}
		else{
			if (sdlEvent == SDL_MOUSEBUTTONUP){
				sprite->show(getButtonUp());
			}
			else if (sdlEvent == SDL_MOUSEMOTION){
				sprite->show(getButtonOver());
			}
			else if (sdlEvent == SDL_MOUSEBUTTONDOWN){
				sprite->show(getButtonDown());
				functocall();
			}
		}
	}
	sprite->show(getButtonOver());

}
