#include <iostream>
#include <sstream>
#include <Windows.h>
#include <SDL.h>
#include <functional>
#include "SDL_image.h"
#include "Button.h"
#include "Sprite.h"


Button::Button(std::function<void(void)> functocall, Sprite* sprite)
{
	this->functocall = functocall;
	this->sprite = sprite;
	
	currState = states.BUTTON_UP;
}

void Button::onButtonDown(int frameNum){
	states.BUTTON_DOWN = frameNum;
}
void Button::onButtonUp(int frameNum){
	states.BUTTON_UP = frameNum;
}
void Button::onButtonOver(int frameNum){
	states.BUTTON_OVER = frameNum;
}

int Button::getButtonDown(){
	return states.buttonDown;
}
int Button::getButtonUp(){
	return states.buttonUp;
}
int Button::getButtonOver(){
	return states.buttonOver;
}

//update() update whether the mouse is inside of the button space
void Button::update(){
	int x, y;
	SDL_GetMouseState(&x, &y);
	
	if (x > body.xPos && x < body.xPos + body.width && y > body.yPos && y < body.yPos + body.height)
	{
		BUTTON_OVER = true;
		currState = states.BUTTON_OVER;
	}
	else
	{
		BUTTON_OVER = false;
		currState = states.BUTTON_UP;
	}
}


//render() will call show()
void Button::render(){
	sprite->show(currState);
}

//handleEvent() could change the current frame being showed
void Button::handleEvent(Uint32 sdlEvent){
	if (BUTTON_OVER){
		if (sdlEvent == SDL_MOUSEBUTTONUP){
			currState = states.BUTTON_UP;
		}
		else if (sdlEvent == SDL_MOUSEBUTTONDOWN){
			currState = states.BUTTON_DOWN;
			functocall();
		}
	}
}
