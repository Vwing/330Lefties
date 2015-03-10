// NameTextBox.h
// ==============================
// Text Box with an additional Nametag Text Box on the top

#pragma once

#include <iostream>
#include <SDL.h>
#include "SDL_ttf.h"
#include "TextBoxResource.h"
#include "TextBox.h"

class NameTextBox
{
	
public:
	NameTextBox(SDL_Renderer* renderer, TTF_Font *font, int fontSize = 10, bool visible = true, enum TextBox::heightOption = TextBox::heightOption::LOW);

	void show();

	// Setter
	void setText(std::string newName, std::string newMessage);
	void setBackground(SDL_Texture* nameBackground, SDL_Texture* messageBackground);
	void setOffset(int x, int y);
	void setAnimation(int displayRate);

private:
	TextBox *nameTextBox;
	TextBox *messageTextBox;

	int offsetX = 20;	// Difference between the namebox and messagebox
	int offsetY = -40;

	std::string name;
	std::string message;
};