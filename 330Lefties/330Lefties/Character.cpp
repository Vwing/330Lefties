#include "Globals.h"
#include "Character.h"
#include "EventManager.h"
#include "SoundManager.h"

Character::Character(Sprite* sprite, int startHP)
: sprite(sprite), currJumpDistance(JUMP_DISTANCE)
{
	body.xPos = sprite->body.xPos;
	body.yPos = sprite->body.yPos;
	body.height = sprite->body.height;
	body.width = sprite->body.width;
	hp = startHP;
	jumping = false;
	falling = false;

	moveSeq.left = "walk left";
	moveSeq.right = "walk right";
	moveSeq.jump = "walk up";
	moveSeq.fall = "walk down";

	//EventManager::getInstance().subscribe(*this, SDL_KEYDOWN);
	Global_RegisterForEvent(this, SDLK_RIGHT);
	Global_RegisterForEvent(this, SDLK_LEFT);
	Global_RegisterForEvent(this, SDLK_SPACE);
	Global_RegisterForEvent(this, Collide);
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
	jumping = true;
	body.yPos -= distance;
	//sprite->movey(-1 * distance);
	sprite->changeSequence(moveSeq.jump);
	currJumpDistance -= distance;
}

void Character::jump(unsigned int distance, bool left){
	jumping = true;
	body.yPos -= distance;
	//sprite->movey(-1 * distance);
	sprite->changeSequence(moveSeq.jump);
	currJumpDistance -= distance;
}

void Character::fall(unsigned int distance){
	jumping = false;
	falling = true;
	body.yPos += distance;
	//sprite->movey(distance);
	sprite->changeSequence(moveSeq.fall);
	currJumpDistance += distance;
}

void Character::handleEvent(Uint32 sdlEvent){
	if (sdlEvent == SDLK_RIGHT)
	{
		moveRight(5);
		if (!jumping && !falling)
			SoundManager::getInstance().playEffect("walk");
	}
	else if (sdlEvent == SDLK_LEFT)
	{
		moveLeft(5);
		if (!jumping && !falling)
			SoundManager::getInstance().playEffect("walk");
	}
	else if (sdlEvent == SDLK_SPACE)
	{
		if (!jumping && !falling)
			jump(3);
	}
}

void Character::update(){
	if (jumping)
	{
		if (currJumpDistance > 0)
		{
			jump(3);
		}
		else
		{
			jumping = false;
			falling = true;
		}
	}
	else if (falling)
	{
		if (currJumpDistance < JUMP_DISTANCE)
		{
			fall(3);
		}
		else
		{
			falling = false;
		}
	}
	sprite->body.xPos = body.xPos;
	sprite->body.yPos = body.yPos;
	sprite->body.screenX = body.screenX;
	sprite->body.screenY = body.screenY;
	sprite->body.layer = body.layer;
}

void Character::render(){
	sprite->render();
}
