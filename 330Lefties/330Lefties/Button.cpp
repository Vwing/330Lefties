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

//update() update whether the mouse is inside of the button space
void Button::update(Uint32 sdlEvent){
	int x, y;
	SDL_GetMouseState(&x, &y);
	inside = true;
	if (x < body.xPos || x > body.xPos + body.width || y < body.yPos || y > body.yPos + body.height)
		inside = false;
}


//render() will call show()
	void Button::render(int buttonPos){
		sprite->show(buttonPos);
	}

//handleEvent() could change the current frame being showed
void Button::handleEvent(Uint32 sdlEvent){
	if (!inside){
		render(getButtonUp());
	}
	else{
		if (sdlEvent == SDL_MOUSEBUTTONUP){
			render(getButtonUp());
		}
		else if (sdlEvent == SDL_MOUSEMOTION){
			render(getButtonOver());
		}
		else if (sdlEvent == SDL_MOUSEBUTTONDOWN){
			render(getButtonDown());
			functocall();
		}
	}
	render(getButtonOver());
}
