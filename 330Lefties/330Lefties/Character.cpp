#include "Globals.h"
#include "Character.h"
#include "EventManager.h"

Character::Character(Sprite* sprite, int startHP){
	this->sprite = sprite;
	body.xPos = sprite->body.xPos;
	body.yPos = sprite->body.yPos;
	hp = startHP;
	moveSeq.left = "walk left";
	moveSeq.right = "walk right";
	moveSeq.jump = "walk up";
	moveSeq.fall = "walk down";

	//EventManager::getInstance().subscribe(*this, SDL_KEYDOWN);
	Global_RegisterForEvent(this, SDLK_RIGHT);
	Global_RegisterForEvent(this, SDLK_LEFT);
	Global_RegisterForEvent(this, SDLK_UP);
	Global_RegisterForEvent(this, SDLK_DOWN);
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

void Character::setPos(int x, int y)
{
	body.xPos = x;
	body.yPos = y;
}

void Character::moveLeft(unsigned int distance){
	body.xPos -= distance;
	//sprite->movex(-1 * distance);
	sprite->changeSequence(moveSeq.left);
}

void Character::moveRight(unsigned int distance){
	body.xPos += distance;
	//sprite->movex(distance);
	sprite->changeSequence(moveSeq.right);
}

void Character::jump(unsigned int distance){
	body.yPos -= distance;
	//sprite->movey(-1 * distance);
	sprite->changeSequence(moveSeq.jump);
}

void Character::fall(unsigned int distance){
	body.yPos += distance;
	//sprite->movey(distance);
	sprite->changeSequence(moveSeq.fall);
}

void Character::handleEvent(Uint32 sdlEvent){
	if (sdlEvent == SDLK_RIGHT)
	{
		moveRight(5);
	}
	else if (sdlEvent == SDLK_LEFT)
	{
		moveLeft(5);
	}
	else if (sdlEvent == SDLK_UP)
	{
		jump(5);
	}
	else if (sdlEvent == SDLK_DOWN)
	{
		fall(5);
	}
}

void Character::update(){
	sprite->body.xPos = body.xPos;
	sprite->body.yPos = body.yPos;
	sprite->body.screenX = body.screenX;
	sprite->body.screenY = body.screenY;
	sprite->body.layer = body.layer;
}

void Character::render(){
	sprite->render();
}
