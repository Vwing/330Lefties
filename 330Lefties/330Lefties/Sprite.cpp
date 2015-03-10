// TODO: code this
#include "Sprite.h"
#include <chrono>
#include <SDL.h>
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <SDL_image.h>


SDL_Texture* loadSpriteTexture(const std::string &file, SDL_Renderer *ren){
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == nullptr){
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "LoadTexture Error");
	}
	return texture;
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst,
	SDL_Rect *clip = nullptr)
{
	SDL_RenderCopy(ren, tex, clip, &dst);
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y,
	SDL_Rect *clip = nullptr)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	if (clip != nullptr){
		dst.w = clip->w;
		dst.h = clip->h;
	}
	else {
		SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	}
	renderTexture(tex, ren, dst, clip);
}

Sprite::Sprite(std::string filePath, SDL_Renderer* ren, int xPos, int yPos)
: renderer(ren), current_seq("")
{
	body.xPos = xPos;
	body.yPos = yPos;
	textures[filePath] = loadSpriteTexture(filePath, ren);
	currentTexture = textures[filePath];
	if (currentTexture == nullptr){
		IMG_Quit();
		SDL_Quit();
		this->~Sprite();
	}
	SDL_QueryTexture(currentTexture, NULL, NULL, &body.width, &body.height);
	makeFrame(currentTexture, xPos, yPos);
}

Sprite::Sprite(std::string filePath, SDL_Renderer* ren, int width, int height, int xPos, int yPos, std::string start_seq)
: renderer(ren), current_seq(start_seq)
{
	body.width = width;
	body.height = height;
	body.xPos = xPos;
	body.yPos = yPos;
	if (filePath != ""){
		textures[filePath] = loadSpriteTexture(filePath, ren);
		currentTexture = textures[filePath];
		if (currentTexture == nullptr){
			IMG_Quit();
			SDL_Quit();
			this->~Sprite();
		}
	}
}

Sprite::~Sprite(void){
	for (unsigned int i = 0; i < frames.size(); ++i){
		SDL_DestroyTexture(frames[i].texture);
	}
	for (auto texture : textures){
		SDL_DestroyTexture(texture.second);
	}
}

void Sprite::setPos(int x, int y){
	body.xPos = x;
	body.yPos = y;
}

void Sprite::movex(int delta){
	body.xPos += delta;
}

void Sprite::movey(int delta){
	body.yPos += delta;
}

int Sprite::getX(){
	return body.xPos;
}

int Sprite::getY(){
	return body.yPos;
}

void Sprite::setTexture(std::string filePath, SDL_Renderer* ren){
	if (textures.count(filePath) == 0){
		SDL_Texture* texture = loadSpriteTexture(filePath, ren);
		if (texture != nullptr){
			textures[filePath] = texture;
		}
		else{
			IMG_Quit();
			SDL_Quit();
		}
	}
	currentTexture = textures[filePath];
}

int Sprite::makeFrame(int x, int y){
	frame f;
	f.texture = currentTexture;
	f.x = x;
	f.y = y;
	frames.push_back(f);
	return frames.size() - 1;
}

int Sprite::makeFrame(SDL_Texture* texture, int x, int y){
	frame f;
	f.texture = texture;
	f.x = x;
	f.y = y;
	frames.push_back(f);
	return frames.size() - 1;
}


int Sprite::makeFrame(std::string filePath, int x, int y){
	frame f;
	f.texture = loadSpriteTexture(filePath, renderer);
	f.x = x;
	f.y = y;
	frames.push_back(f);
	return frames.size() - 1;
}

int Sprite::addFrameToSequence(std::string seqName, int frameIndex, unsigned int duration){
	//sequenceList[seqName].first.push_back(frameIndex);
	//return sequenceList[seqName].first.size();
	sequenceList[seqName].frameVector.push_back(std::make_pair(frameIndex, duration));
	return sequenceList[seqName].frameVector.size();
}

void Sprite::show(int frameIndex){
	SDL_Rect clip;
	clip.x = frames[frameIndex].x;
	clip.y = frames[frameIndex].y;
	clip.w = body.width;
	clip.h = body.height;
	renderTexture(frames[frameIndex].texture, renderer, body.screenX, body.screenY, &clip);
}

void Sprite::show(std::string sequence){
	if (sequenceList[sequence].currentIndex >= sequenceList[sequence].frameVector.size()){
		sequenceList[sequence].currentIndex = 0;
	}
	show(sequenceList[sequence].frameVector[sequenceList[sequence].currentIndex].first);
	auto currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	if (sequenceList[sequence].frameVector[sequenceList[sequence].currentIndex].second == 0 || currentTime >= frameStartTime + sequenceList[sequence].frameVector[sequenceList[sequence].currentIndex].second){
		++sequenceList[sequence].currentIndex;
		frameStartTime = currentTime;
	}
	//if (sequenceList[sequence].second >= sequenceList[sequence].first.size()){
	//	sequenceList[sequence].second = 0;
	//}
	//show(sequenceList[sequence].first[sequenceList[sequence].second]);
	//++sequenceList[sequence].second;
}

void Sprite::changeSequence(std::string seq){
	current_seq = seq;
}

void Sprite::handleEvent(Uint32 sdlEvent){

}

void Sprite::update(){

}

void Sprite::render(){
	if (current_seq == "" && !frames.empty()){
		show(0);
	}
	else{
		show(current_seq);
	}
}