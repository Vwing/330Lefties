#pragma once

#include "SDL.h"
#include <vector>
#include <map>
#include <functional>
#include "Sprite.h"
#include "UI_Element.h"

struct ButtonPress{
	int buttonOver = 0;
	int buttonUp = 1;
	int buttonDown = 2;
};

class Button : public UI_Element{
public:
	Button(std::function<void(void)> functocall, Sprite* sprite);
	void handleEvent(Uint32 sdlEvent);
	void onButtonDown(int frameNum); // Change frame for Button Down
	void onButtonUp(int frameNum); // Change frame for Button Up
	void onButtonOver(int frameNum); // Change frame for Button Over
	int getButtonDown(); // Get frame for Button Down
	int getButtonUp(); // Get frame for Button Up
	int getButtonOver(); // Get frame for Button Over
private:
	SDL_Renderer* renderer;
	std::string resPath, spritesheet;
	std::function<void(void)> functocall;
	Sprite* sprite;
	ButtonPress press;
};
