#pragma once
#include "SDL_ttf.h"

class TextBoxResource{

public:
	static TextBoxResource *getInstance(){
		static TextBoxResource *instance = new TextBoxResource();
		return instance;
	}

	~TextBoxResource(){}

	void loadFont(std::string filePath, int pointsize)
	{
		sampleFont = TTF_OpenFont(filePath.c_str(), pointsize);
	}

	TTF_Font* getFont()
	{
		return sampleFont;
	}

	TTF_Font *sampleFont;
	SDL_Texture *textboxBackgroundTexture;
	SDL_Texture *portraitTexture;

private:
	TextBoxResource(){}
};