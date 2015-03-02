// TODO: code this
#include "Sprite.h"

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

Sprite::Sprite(int width, int height, SDL_Renderer* ren, int xPos, int yPos, std::string start_seq){
	body.width = width;
	body.height = height;
	renderer = ren;
	body.xPos = xPos;
	body.yPos = yPos;
	current_seq = start_seq;
}

Sprite::~Sprite(void){
	for (unsigned int i = 0; i < frames.size(); ++i){
		SDL_DestroyTexture(frames[i].texture);
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

int Sprite::makeFrame(SDL_Texture* texture, int x, int y){
	frame f;
	f.texture = texture;
	f.x = x;
	f.y = y;
	frames.push_back(f);
	return frames.size() - 1;
}

int Sprite::addFrameToSequence(std::string seqName, int frameIndex){
	sequenceList[seqName].first.push_back(frameIndex);
	return sequenceList[seqName].first.size();
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
	if (sequenceList[sequence].second >= sequenceList[sequence].first.size()){
		sequenceList[sequence].second = 0;
	}
	show(sequenceList[sequence].first[sequenceList[sequence].second]);
	++sequenceList[sequence].second;
}

void Sprite::changeSequence(std::string seq){
	current_seq = seq;
}

void Sprite::handleEvent(SDL_Event sdlEvent){

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