#include <iostream>
#include <sstream>
#include <Windows.h>
#include <SDL.h>
#include <functional>
#include "SDL_image.h"
#include "Button.h"
#include "Sprite.h"
#include "Globals.h"

Button::Button(Sprite* sprite, Uint32 onDownEvent)
: sprite(sprite), onDownEvent(onDownEvent)
{
	currState = states.BUTTON_UP;

	BUTTON_IS_OVER = false;
	BUTTON_IS_DOWN = false;

	Global_RegisterForEvent(this, SDL_MOUSEBUTTONUP);
	Global_RegisterForEvent(this, SDL_MOUSEBUTTONDOWN);
}

// Show the frame made by xPos, yPos
void Button::onButtonDown(int xPos, int yPos){
	states.BUTTON_DOWN = sprite->makeFrame(xPos, yPos);
}
// Show the frame made by xPos, yPos
void Button::onButtonUp(int xPos, int yPos){
	states.BUTTON_UP = sprite->makeFrame(xPos, yPos);
}
// Show the frame made by xPos, yPos
void Button::onButtonOver(int xPos, int yPos){
	states.BUTTON_OVER = sprite->makeFrame(xPos, yPos);
}

//update() update whether the mouse is inside of the button space
void Button::update(){
	int x, y;
	SDL_GetMouseState(&x, &y);
	
	if (x > sprite->body.xPos && x < sprite->body.xPos + sprite->body.width && y > sprite->body.yPos && y < sprite->body.yPos + sprite->body.height)
	{
		BUTTON_IS_OVER = true;
		currState = states.BUTTON_OVER;
	}
	else if (!BUTTON_IS_DOWN)
	{
		BUTTON_IS_OVER = false;
		currState = states.BUTTON_UP;
	}
}


//render() will call show()
void Button::render(){
	sprite->show(currState);
}

//handleEvent() could change the current frame being showed
void Button::handleEvent(Uint32 sdlEvent){
	if (BUTTON_IS_OVER){
		if (sdlEvent == SDL_MOUSEBUTTONUP){
			currState = states.BUTTON_UP;
			BUTTON_IS_DOWN = false;
		}
		else if (sdlEvent == SDL_MOUSEBUTTONDOWN){
			currState = states.BUTTON_DOWN;
			BUTTON_IS_DOWN = true;
			EventManager::getInstance().DispatchEvent(onDownEvent);
		}
	}
}
