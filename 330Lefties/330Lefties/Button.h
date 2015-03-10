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

class Button : public UI_Element{
public:
	Button(std::function<void(void)> functocall, Sprite* sprite);
	//update() update whether the mouse is inside of the button space, render() will call show() and handleEvent() could change the current frame being showed
	void handleEvent(Uint32 sdlEvent);
	void update();
	void render();
	void onButtonDown(int frameNum); // Change frame for Button Down
	void onButtonUp(int frameNum); // Change frame for Button Up
	void onButtonOver(int frameNum); // Change frame for Button Over
	int getButtonDown(); // Get frame for Button Down
	int getButtonUp(); // Get frame for Button Up
	int getButtonOver(); // Get frame for Button Over
private:
	std::function<void(void)> functocall;
	Sprite* sprite;
	ButtonStates states;
	int currState;
	bool BUTTON_OVER;
};
