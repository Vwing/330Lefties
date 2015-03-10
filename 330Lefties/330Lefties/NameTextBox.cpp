#include "NameTextBox.h"

	NameTextBox::NameTextBox(SDL_Renderer* renderer, TTF_Font *font, int fontSize, bool visible, enum TextBox::heightOption){
		nameTextBox = new TextBox(renderer, font, fontSize, visible);
		messageTextBox = new TextBox(renderer, font, fontSize, visible);
		nameTextBox->setPosition(nameTextBox->getPosX() + offsetX, nameTextBox->getPosY() + offsetY);
		nameTextBox->setFontSize(nameTextBox->getFontSize() + 5);
	};

	void NameTextBox::show(){
		messageTextBox->show();
		nameTextBox->show();
	}

	// Setter
	void NameTextBox::setText(std::string newName, std::string newMessage){
		name = newName;
		message = newMessage;
		nameTextBox->setMessage(name);
		messageTextBox->setMessage(message);
	}

	void NameTextBox::setBackground(SDL_Texture* nameBackground, SDL_Texture* messageBackground){
		if (nameBackground != NULL){
			nameTextBox->setBackground(nameBackground);
		}
		if (messageBackground != NULL){
			messageTextBox->setBackground(messageBackground);
		}
	}

	void NameTextBox::setOffset(int x, int y){
		offsetX = x;
		offsetY = y;
	}

	void NameTextBox::setAnimation(int displayRate){
		messageTextBox->setDisplayRate(displayRate);
		messageTextBox->setAnimationRequested(true);
	}