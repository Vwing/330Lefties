#include "TextBox.h"


/**
* Initialize a TextBox object
* @param r The renderer we want to draw in
// TO DO UPDATE
*/
TextBox::TextBox(SDL_Renderer* _renderer, TTF_Font *_font, int _fontSize, bool _visible, TextBox::heightOption height){
	renderer = _renderer;
	visible = _visible;
	//color = { 0, 0, 0 };
	
	font = _font;
	fontSize = _fontSize;

	// Set box position based on height enumeration
	if (TextBox::heightOption::HIGH == height){
		posX = 0;
		posY = 4;
	}
	else if (TextBox::heightOption::MID == height){
		posX = 0;
		posY = 204;
	}
	else if (TextBox::heightOption::LOW == height){
		posX = 0;
		posY = 324;
	}
}

TextBox::~TextBox(){

	if (messageTexture != NULL){
		SDL_DestroyTexture(messageTexture);
	}
	if (backgroundTexture != NULL){
		SDL_DestroyTexture(backgroundTexture);
	}

	TTF_CloseFont(font);
}

void TextBox::show(){
	tempMessage = message;
	if (animationRequested == true){
		animationRequested = false;
		animationIsOn = true;
		animationStartTime = SDL_GetTicks();
		setWindowDst();
	}

	if (animationIsOn == true){
		int duration = SDL_GetTicks() - animationStartTime;
		int numberCharacters = duration / displayRate;

		 tempMessage = message.substr(0, numberCharacters);

		if (numberCharacters >= message.length()){
			animationIsOn = false;
		}
	}

	//We need to first render to a surface as that's what TTF_RenderText returns, then
	//load that surface into a texture
	if (tempMessage == ""){
		return;
	}
	SDL_Surface *surf = TTF_RenderText_Blended_Wrapped(font, tempMessage.c_str(), color, 640);
	if (surf == nullptr){
		TTF_CloseFont(font);
		yikes("failSurface");
	}
	messageTexture = SDL_CreateTextureFromSurface(renderer, surf);
	if (messageTexture == nullptr){
		yikes("failTexture");
	}

	// Free Surface
	SDL_FreeSurface(surf);

	// Render
	SDL_Rect dst;
	dst.x = posX;
	dst.y = posY;
	dst.w = surf->w;
	dst.h = surf->h;

	if (backgroundTexture != NULL){
		if (animationIsOn == true){
			SDL_RenderCopy(renderer, backgroundTexture, NULL, &windowDst);
		}
		else{
			SDL_RenderCopy(renderer, backgroundTexture, NULL, &dst);
		}
	}
	SDL_RenderCopy(renderer, messageTexture, NULL, &dst);
}

void TextBox::clear(){
	// TODO
}

void TextBox::setWindowDst(){
	SDL_Surface *surf = TTF_RenderText_Blended_Wrapped(font, message.c_str(), color, 640);
	if (surf == nullptr){
		TTF_CloseFont(font);
		yikes("failSurface");
	}
	messageTexture = SDL_CreateTextureFromSurface(renderer, surf);
	if (messageTexture == nullptr){
		yikes("failTexture");
	}

	// Free Surface
	SDL_FreeSurface(surf);

	// Render
	SDL_Rect dst;
	dst.x = posX;
	dst.y = posY;
	dst.w = surf->w;
	dst.h = surf->h;

	windowDst = dst;
}

// We need to handle error conditions such as not being able to find/open/use specified font
void TextBox::yikes(std::string message){ // for error conditions
	if (message == "failTTF_Init"){
		std::cout << "Yikes! TTF_Init failed (returned 0).";
	}
	else if (message == "failOpen"){
		std::cout << "Yikes! TTF_OpenFont failed to open the font. (returned nullptr)";
	}
	else if (message == "failSurface"){
		std::cout << "Yikes! The surface failed to be created. (returned nullptr)";
	}
	else if (message == "failTexture"){
		std::cout << "Yikes! The texture failed to be created. (returned nullptr)";
	}
	else{
		std::cout << "Yikes! Unidentified error occurred.";
	}
}