//#include <iostream>
//#include <sstream>
//#include <string>
//#include <SDL.h>
//#include "res_path.h"
//#include "cleanup.h"
//#include "SDL_image.h"
//#include "TextBox.h"
//#include "NameTextBox.h"
//#include "PortraitTextBox.h"
//#include "Windows.h"
//#include "TextBoxResource.h"
//
//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;
//
///**
//* Log an SDL error with some error message to the output stream of our choice
//* @param os The output stream to write the message to
//* @param msg The error message to write, format will be msg error: SDL_GetError()
//*/
//void logSDLError(std::ostream &os, const std::string &msg){
//	std::ostringstream errMsg;
//	errMsg << "message: " << msg << " error: " << SDL_GetError() << std::endl;
//	OutputDebugString(errMsg.str().c_str());
//	os << msg << " error: " << SDL_GetError() << std::endl;
//}
//
///**
//* Loads an image into a texture on the rendering device
//* @param file The image file to load
//* @param ren The renderer to load the texture onto
//* @return the loaded texture, or nullptr if something went wrong.
//*/
//SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren){
//	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
//	if (texture == nullptr){
//		logSDLError(std::cout, "LoadTexture");
//	}
//	return texture;
//}
//
///**
//* Draw an SDL_Texture to an SDL_Renderer at position x, y, with some desired
//* width and height
//* @param tex The source texture we want to draw
//* @param ren The renderer we want to draw to
//* @param x The x coordinate to draw to
//* @param y The y coordinate to draw to
//* @param w The width of the texture to draw
//* @param h The height of the texture to draw
//*/
//void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h){
//	//Setup the destination rectangle to be at the position we want
//	SDL_Rect dst;
//	dst.x = x;
//	dst.y = y;
//	dst.w = w;
//	dst.h = h;
//	SDL_RenderCopy(ren, tex, NULL, &dst);
//}
//
///**
//* Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
//* the texture's width and height
//* @param tex The source texture we want to draw
//* @param ren The renderer we want to draw to
//* @param x The x coordinate to draw to
//* @param y The y coordinate to draw to
//*/
//void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
//	int w, h;
//	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
//	renderTexture(tex, ren, x, y, w, h);
//}
//
//
//// Ceci's
//// Load all the images needed for the textBox
//bool onInit(){
//	return true;
//}
//
//int main(int argc, char **argv){
//	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
//		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
//		return 1;
//	}
//
//	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
//		logSDLError(std::cout, "IMG_Init");
//		SDL_Quit();
//		return 1;
//	}
//
//	SDL_Window *window = SDL_CreateWindow("TextBoxDemo", 800, 100, SCREEN_WIDTH,
//		SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//	if (window == nullptr){
//		logSDLError(std::cout, "CreateWindow");
//		SDL_Quit();
//		return 1;
//	}
//	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
//		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//	if (renderer == nullptr){
//		logSDLError(std::cout, "CreateRenderer");
//		cleanup(window);
//		SDL_Quit();
//		return 1;
//	}
//	// Init SDL_ttf
//	if (TTF_Init() != 0){
//		/*yikes("failTTF_Init");*/
//		SDL_Quit();
//	}
//	const std::string resPath = getResourcePath("Homework4");
//	// ======================================================
//	// Loading
//	TextBoxResource *TextBoxResource = TextBoxResource::getInstance();
//
//	// Open the font
//	std::string filePath = resPath + "SpecialElite.ttf";
//	TextBoxResource->sampleFont = TTF_OpenFont(filePath.c_str(), 30);
//	//if (sampleFont == nullptr){
//	//	//print error
//	//}
//
//	filePath = resPath + "windowbg.png";
//
//	SDL_Surface *temp = IMG_Load(filePath.c_str());
//	TextBoxResource->textboxBackgroundTexture = SDL_CreateTextureFromSurface(renderer, temp);
//
//
//	filePath = resPath + "portrait.png";
//
//	SDL_Surface *temp2 = IMG_Load(filePath.c_str());
//	TextBoxResource->portraitTexture = SDL_CreateTextureFromSurface(renderer, temp2);
//
//	// Free Surface
//	SDL_FreeSurface(temp);
//
//	// ===================================================================================================================================
//
//	
//	TextBox* TextBox1 = new TextBox(renderer, TextBoxResource->sampleFont, 30, true);
//	TextBox1->setMessage("Hi, this is a plain textbox. It recognizes \\n \n and has smart line wrapping. Hello hello hello");
//
//
//	TextBox* TextBox2 = new TextBox(renderer, TextBoxResource->sampleFont, 30, true);
//	TextBox2->setDisplayRate(250);
//	
//	TextBox2->setAnimationRequested(true);
//	TextBox2->setMessage("Hi, I am a plain textbox with animated text. You can change the text speed by changing the variable Display rate. Neat!");
//	TextBox2->setDisplayRate(75);
//
//
//	NameTextBox* name = new NameTextBox(renderer, TextBoxResource->sampleFont);
//	name->setBackground(TextBoxResource->textboxBackgroundTexture, TextBoxResource->textboxBackgroundTexture);
//	name->setOffset(0, -30);
//
//	PortraitTextBox* portrait = new PortraitTextBox(renderer, TextBoxResource->sampleFont, TextBoxResource->portraitTexture);
//	portrait->setBackground(TextBoxResource->textboxBackgroundTexture, TextBoxResource->textboxBackgroundTexture);
//	portrait->setPortraitDimensions(300, 416);
//
//	PortraitTextBox* portrait2 = new PortraitTextBox(renderer, TextBoxResource->sampleFont, TextBoxResource->portraitTexture);
//	portrait2->setBackground(TextBoxResource->textboxBackgroundTexture, TextBoxResource->textboxBackgroundTexture);
//	portrait2->setPortraitDimensions(300, 416);
//	portrait2->setAnimation(40);
//	portrait2->setText("Robin", "Animated text makes it look like \n the character is talking. Hello!\n\n\n\n\n");
//	// ===================================================================================================================================
//
//
//
//	SDL_Texture *image = loadTexture(resPath + "image.png", renderer);
//	if (image == nullptr){
//		cleanup(image, renderer, window);
//		logSDLError(std::cout, "loadTexture");
//		IMG_Quit();
//		SDL_Quit();
//		return 1;
//	}
//
//	int iW, iH;
//	SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
//	int BGx = SCREEN_WIDTH / 2 - iW / 2;
//	int BGy = SCREEN_HEIGHT / 2 - iH / 2;
//
//	int counter = 0;
//
//	SDL_Event e;
//	bool quit = false;
//
//
//	while (!quit){
//		while (SDL_PollEvent(&e))
//		{
//			if (e.type == SDL_QUIT)
//			{
//				quit = true;
//			}
//			if (e.type == SDL_KEYDOWN)
//			{
//				if (e.key.keysym.sym == SDLK_RETURN)
//					BGx += 3;
//			}
//		}
//
//		//Render the scene
//		SDL_RenderClear(renderer);
//		renderTexture(image, renderer, BGx, BGy);
//
//
//		counter++;
//
//		if (counter < 200){
//			TextBox1->show();
//		}
//		else if (counter < 400){
//			TextBox1->setBackground(TextBoxResource->textboxBackgroundTexture);
//			TextBox1->setMessage("You can keep the background transparent, or use an image like here.\n\n\n\n");
//			TextBox1->show();
//		}
//		else if (counter < 600){
//			name->setText("Namebox", "A textbox that has a nametag. \n\n\n\n\n");
//			name->show();
//		}
//		else if (counter < 800){
//			portrait->setText("Robin", "Hi, this namebox has a character portrait to go with it.\n\n\n\n");
//			portrait->show();
//		}
//		else {
//			portrait2->show();
//		}
//	
//
//		SDL_RenderPresent(renderer);
//	}
//
//	cleanup(image, renderer, window);
//	delete TextBox1;
//
//	IMG_Quit();
//	SDL_Quit();
//
//	return 0;
//}
