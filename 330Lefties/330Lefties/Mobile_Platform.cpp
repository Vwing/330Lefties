#pragma once
#include "Mobile_Platform.h"

Mobile_Platform::Mobile_Platform(Sprite* s, std::string h)
{
	sprite = s;
	currentseq = h;
	Unit::enableAI = true;
	Unit::enablePhysics = true;
	body.xPos = x;
	body.yPos = y;
	ai = Unit::createAI(x, y);
	ai->patrol(10, 0, 60);
}

Mobile_Platform::~Mobile_Platform()
{
	delete sprite;
}

void Mobile_Platform::update()
{
	//do the thing: left and right
	ai->update();
	body.xPos = ai->getX();
	body.yPos = ai->getY();
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
