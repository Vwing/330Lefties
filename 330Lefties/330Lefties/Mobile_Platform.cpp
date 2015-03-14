
#include "Mobile_Platform.h"

Mobile_Platform::Mobile_Platform(Sprite* s)
{
	sprite = s;
	body.xPos = sprite->body.xPos;
	body.yPos = sprite->body.yPos;
	body.height = sprite->body.height;
	body.width = sprite->body.width;

	enableAI = true;
	enablePhysics = true;

	createAI();
	ai->patrol(10, 0, 60);
}

Mobile_Platform::~Mobile_Platform()
{
	delete sprite, ai;
}

void Mobile_Platform::update()
{
	//do the thing: left and right
	ai->update();
	body.xPos = ai->getX();
	body.yPos = ai->getY();
	
	if (!immovable)
	{
		body.xPos += velocity.x;
		body.yPos += velocity.y;
	}
	
	sprite->body.xPos = body.xPos;
	sprite->body.yPos = body.yPos;
	sprite->body.screenX = body.screenX;
	sprite->body.screenY = body.screenY;
	sprite->body.layer = body.layer;
}

void Mobile_Platform::render()
{
	sprite->render();
}

void Mobile_Platform::handleEvent(Uint32 e)
{
	
}
