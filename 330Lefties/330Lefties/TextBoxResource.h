#pragma once
#include "SDL_ttf.h"

class TextBoxResource{

public:
	static TextBoxResource *getInstance(){
		static TextBoxResource *instance = new TextBoxResource();
		return instance;
	}

	~TextBoxResource(){}

	TTF_Font *sampleFont;
	SDL_Texture *textboxBackgroundTexture;
	SDL_Texture *portraitTexture;

private:
	TextBoxResource(){}
};