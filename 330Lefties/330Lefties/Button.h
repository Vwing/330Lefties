#pragma once

#include "SDL.h"
#include <vector>
#include <map>
#include <functional>
#include "Sprite.h"
#include "UI_Element.h"

class Button : public UI_Element{
public:
	Button(SDL_Renderer* ren, std::string resPath, std::string spritesheet, std::function<void(void)> functocall, Sprite* sprite);
	~Button(void);
	void logSDLError(std::ostream &os, const std::string &msg);
	SDL_Texture* loadTexture();
	void handleEvent(Uint32 sdlEvent);
private:
	SDL_Renderer* renderer;
	std::string resPath, spritesheet;
	std::function<void(void)> functocall;
	Sprite* sprite;
};
