#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <Windows.h>
#include <SDL.h>
#include "SDL_image.h"
#include "Button.h"
#include <windows.h>
#include <functional>

Button::Button(int width, int height, int x, int y, SDL_Renderer* ren, std::string resPath, std::string spritesheet, std::function<void(void)> functocall)
{
	this->width = width;
	this->height = height;
	this->currX = x;
	this->currY = y;
	this->renderer = ren;
	this->resPath = resPath;
	this->spritesheet = spritesheet;
	this->functocall = functocall;
}

void Button::logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
	std::ostringstream errMsg;
	errMsg << " error: " << SDL_GetError() << std::endl;
	OutputDebugString(errMsg.str().c_str());
}

SDL_Texture* Button::loadTexture(){
	const std::string file = resPath + spritesheet;
	SDL_Texture* texture = IMG_LoadTexture(renderer, file.c_str());
	if (texture == nullptr){
		logSDLError(std::cout, "LoadTexture");
	}
	return texture;
}

// set the current X and Y location of the Button
void Button::setPos(int x, int y){
	this->currX = x;
	this->currY = y;
}

// makeFrame returns the unique index of the frame
int Button::makeFrame(SDL_Texture* texture, int x, int y)
{
	frame new_frame;
	new_frame.texture = texture; // spritesheet
	new_frame.x = x; // x position on spritesheet
	new_frame.y = y; // y position on spritesheet
	frames.push_back(new_frame);
	return frames.size() - 1;
}

// addFrameToSequence returns the number of frames in the sequence after the add
int Button::addFrameToSequence(std::string seqName, int frameIndex)
{
	sequenceList[seqName].push_back(frameIndex);
	return sequenceList[seqName].size() - 1;
}


// return current X location of Button on the window
int Button::getX(){
	return currX;
}

// return current X location of Button on the window
int Button::getY(){
	return currY;
}

// show(int) renders the frame with the specified frameIndex
void Button::show(int frameIndex){
	SDL_Rect dst, clip;
	dst.x = currX; // location X on window
	dst.y = currY; // location Y on window
	dst.w = width; // width of Button on window
	dst.h = height; // height of Button on window
	clip.x = frames[frameIndex].x; // location X on spritesheet
	clip.y = frames[frameIndex].y; // location Y on spritesheet
	clip.w = width; // width of Button on spritesheet
	clip.h = height; // height of Button on spritesheet
	SDL_RenderCopy(renderer, frames[frameIndex].texture, &clip, &dst);
}

// show(string) cycles through all frames in the specified sequence, one per call
void Button::show(std::string sequence){
	if (sequenceIndex == sequenceList[sequence].size()){
		sequenceIndex = 0;
	}
	show(sequenceList.at(sequence)[sequenceIndex]);
	sequenceIndex++;
}
/*
void Button::start(Uint32* e){
	addFrameToSequence("mouse up", makeFrame(loadTexture(), 0, 0));
	addFrameToSequence("mouse down", makeFrame(loadTexture(), 0, height));
	std::string button = "mouse up";
	
	if (e->type == SDL_MOUSEBUTTONUP || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEMOTION){
		int x, y;
		SDL_GetMouseState(&x, &y);
		bool inside = true;

		if (x < currX /*Mouse is left of the button || x > currX + width /*Mouse is right of the button
			|| y < currY /*Mouse is above the button || y > currY + height /*Mouse is below the button)
			inside = false;
		if (!inside){
			button = "mouse up";
			show(button.c_str());
		}
		else{
			switch (e->type){
			case SDL_MOUSEMOTION:
				button = "mouse up";
				break;
			case SDL_MOUSEBUTTONUP:
				button = "mouse up";
				break;
			case SDL_MOUSEBUTTONDOWN:
				button = "mouse down";
				functocall();
				break;
			}
			show(button.c_str());
		}
	}
	show(button.c_str());
	
}*/
