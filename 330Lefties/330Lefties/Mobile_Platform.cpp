#pragma once
#include "Mobile_Platform.h"

Mobile_Platform::Mobile_Platform(Sprite* s)
{
	sprite = s;
}

Mobile_Platform::~Mobile_Platform()
{
	delete sprite;
}

void Mobile_Platform::update()
{
	if (timer < 10 || timer >= 30 && timer < 40)
	{
		sprite->movex(1);//right ten times
		x++;
	}
	else if (timer >= 10 && timer < 30)
	{
		sprite->movex(-1);//left 20
	}
	else if (timer >= 40)
	{
		timer = 0;
	}
	timer++;
}

void Mobile_Platform::render()
{
	sprite->show(currentseq);//currentseq is set to "" by default
}

void Mobile_Platform::handleEvent(Uint32 e)
{
	
}
