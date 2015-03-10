// Portrait TextBox
// ==============================
// Text Box with an additional Nametag Text Box on the top, as well as an image (such as a character portrait)

#pragma once

#include <iostream>
#include <SDL.h>
#include "SDL_ttf.h"
#include "TextBoxResource.h"
#include "TextBox.h"

class PortraitTextBox
{

public:
	PortraitTextBox(SDL_Renderer* renderer, TTF_Font *font, SDL_Texture *portrait, int fontSize = 10, bool visible = true, enum TextBox::heightOption = TextBox::heightOption::LOW);

	void show();

	// Setter
	void setText(std::string newName, std::string newMessage);
	void setBackground(SDL_Texture* nameBackground, SDL_Texture* messageBackground);
	void setNameOffset(int x, int y);
	void setPortraitOffset(int x, int y);
	void setAnimation(int displayRate);

	// Setter
	inline void setPortraitDimensions(int h, int w){
		portraitTextureH = h;
		portraitTextureW = w;
	}

private:
	SDL_Renderer* renderer = NULL;
	TextBox *nameTextBox;
	TextBox *messageTextBox;
	SDL_Texture *portraitTexture;

	int offsetNameX = 20;	// Difference between the namebox and messagebox
	int offsetNameY = -40;
	int offsetPortraitX = 300;
	int offsetPortraitY = 0;

	int portraitTextureH = 0;
	int portraitTextureW = 0;

	std::string message;
	std::string name;
};