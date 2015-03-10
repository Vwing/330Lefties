// TextBox.h
// ==============================
// Cecilia Bishton: An updated version of Texty.

#pragma once

#include <iostream>
#include <SDL.h>
#include "SDL_ttf.h"
#include "TextBoxResource.h"

class TextBox
{

public:
	enum heightOption { HIGH, MID, LOW};	// Enumerations to set textbox height conveniently
	
	TextBox(SDL_Renderer* renderer, TTF_Font *font, int fontSize = 10, bool visible = true, enum heightOption = LOW);
	~TextBox();

	void show();	// Shows the text
	void clear();	// Clears the text

	// Setters
	inline void setMessage(std::string newMessage) { message = newMessage; };
	inline void setFont(TTF_Font *newFont){ font = newFont; }
	inline void setFontSize(int newSize){ fontSize = newSize; }
	inline void setPosition(int newX, int newY){ posX = newX; posY = newY; }
	inline void setBackground(SDL_Texture * newBackground) { backgroundTexture = newBackground; }
	inline void setColor(SDL_Color newColor){ color = newColor; }
	inline void setDisplayRate(int newRate){ displayRate = newRate; }
	inline void setAnimationRequested(bool setting){ animationRequested = setting; }
	

	// Getter
	inline int getPosX(){ return posX; };
	inline int getPosY(){ return posY; };
	inline int getFontSize(){ return fontSize; };

private:
	int posX = 0;	// Top left corner
	int posY = 0;

	std::string message;

	std::string backgroundFile;
	int fontSize = 10;
	
	SDL_Renderer* renderer = NULL;
	TTF_Font* font = NULL;

	SDL_Texture* backgroundTexture = NULL;		// Texture for the background image (Window GUI)
	SDL_Texture* messageTexture = NULL;			// Texture for the printed message
	SDL_Color color;							// Text color

	bool error = false;
	
	// Animation variables
	int displayRate = 0;	// Miliseconds
	int animationStartTime = 0;
	bool animationIsOn = false;
	bool animationRequested = false;
	std::string tempMessage = "";
	SDL_Rect windowDst;
	void setWindowDst();

	bool visible = false;
	void yikes(std::string message); // for error conditions


};