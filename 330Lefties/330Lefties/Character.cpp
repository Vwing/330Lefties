#include "Character.h"
#include "EventManager.h"

Character::Character(int width, int height, SDL_Renderer* ren, int startX, int startY, std::string start_seq, int startHP) : Sprite(width, height, ren, startX, startY, start_seq){
	//gravity = true;
	hp = startHP;
	moveSeq.left = "walk left";
	moveSeq.right = "walk right";
	moveSeq.jump = "walk up";
	moveSeq.fall = "walk down";
	
	EventManager::getInstance().subscribe(this, SDL_KEYDOWN);
}

Character::~Character(void){
}

void Character::changeHP(int deltaHP){
	hp += deltaHP;
}

int Character::getHP(){
	return hp;
}

void Character::changeSequenceName(std::string movementType, std::string seq){
	if (movementType == "left"){
		moveSeq.left = seq;
	}
	else if (movementType == "right"){
		moveSeq.right = seq;
	}
	else if (movementType == "jump"){
		moveSeq.jump = seq;
	}
	else if (movementType == "fall"){
		moveSeq.fall = seq;
	}
}

void Character::moveLeft(unsigned int distance){
	movex(-1 * distance);
	changeSequence(moveSeq.left);
}

void Character::moveRight(unsigned int distance){
	movex(distance);
	changeSequence(moveSeq.right);
}

void Character::jump(unsigned int distance){
	movey(-1 * distance);
	changeSequence(moveSeq.jump);
}

void Character::fall(unsigned int distance){
	movey(distance);
	changeSequence(moveSeq.fall);
}

void Character::handleEvent(SDL_Event sdlEvent){
	if (sdlEvent.type == SDL_KEYDOWN){
		if (sdlEvent.key.keysym.sym == SDLK_RIGHT)
		{
			moveRight(5);
		}
		else if (sdlEvent.key.keysym.sym == SDLK_LEFT)
		{
			moveLeft(5);
		}
		else if (sdlEvent.key.keysym.sym == SDLK_UP)
		{
			jump(5);
		}
	}
}

void Character::update(){
}

void Character::render(){
	show(current_seq);
}
