#include "PortraitTextBox.h"


PortraitTextBox::PortraitTextBox(SDL_Renderer* _renderer, TTF_Font *font, SDL_Texture *portrait, int fontSize, bool visible, enum TextBox::heightOption){
	renderer = _renderer;
	nameTextBox = new TextBox(renderer, font, fontSize, visible);
	messageTextBox = new TextBox(renderer, font, fontSize, visible);
	portraitTexture = portrait;

	nameTextBox->setPosition(nameTextBox->getPosX() + offsetNameX, nameTextBox->getPosY() + offsetNameY);
	nameTextBox->setFontSize(nameTextBox->getFontSize() + 5);
}

void PortraitTextBox::show(){

	// Render
	SDL_Rect dst;
	dst.x = nameTextBox->getPosX() + offsetPortraitX;
	dst.y = nameTextBox->getPosX() + offsetPortraitY;
	dst.w = portraitTextureH;
	dst.h = portraitTextureW;

	if (portraitTexture != NULL){
		SDL_RenderCopy(renderer, portraitTexture, NULL, &dst);
	}

	messageTextBox->show();
	nameTextBox->show();
}


// Setter
void PortraitTextBox::setText(std::string newName, std::string newMessage){
	name = newName;
	message = newMessage;
	nameTextBox->setMessage(name);
	messageTextBox->setMessage(message);
}

void PortraitTextBox::setBackground(SDL_Texture* nameBackground, SDL_Texture* messageBackground){
	if (nameBackground != NULL){
		nameTextBox->setBackground(nameBackground);
	}
	if (messageBackground != NULL){
		messageTextBox->setBackground(messageBackground);
	}
}

void PortraitTextBox::setNameOffset(int x, int y){
	offsetNameX = x;
	offsetNameY = y;
}

void PortraitTextBox::setPortraitOffset(int x, int y){
	offsetPortraitX = x;
	offsetPortraitY = y;
}

void PortraitTextBox::setAnimation(int displayRate){
	messageTextBox->setDisplayRate(displayRate);
	messageTextBox->setAnimationRequested(true);
}