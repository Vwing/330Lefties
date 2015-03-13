#pragma once

#include "SDL.h"
#include <vector>
#include <map>
#include <functional>
#include "Sprite.h"
#include "UI_Element.h"

struct ButtonStates{
	int BUTTON_UP = 0;
	int BUTTON_DOWN = 1;
	int BUTTON_OVER = 2;
};

class Button : public UI_Element {
public:
	Button(Sprite* sprite, Uint32 onDownEvent);
	//update() update whether the mouse is inside of the button space, render() will call show() and handleEvent() could change the current frame being showed
	void handleEvent(Uint32 sdlEvent);
	void update();
	void render();
	void onButtonDown(int xPos, int yPos); // Specify location of frame for Button Down
	void onButtonUp(int xPos, int yPos); // Specify location of frame for Button Up
	void onButtonOver(int xPos, int yPos); // Specify location of frame for Button Over
	int getButtonDown(); // Get frame for Button Down
	int getButtonUp(); // Get frame for Button Up
	int getButtonOver(); // Get frame for Button Over

private:
	Uint32 onDownEvent;
	Sprite* sprite;
	ButtonStates states;
	int currState;
	bool BUTTON_IS_OVER;
	bool BUTTON_IS_DOWN;
};
