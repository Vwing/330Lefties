#pragma once
#include "BasicNPC.h"
#include "random"
#include "time.h"

BasicNPC::BasicNPC(Sprite* sprt, std::string h)
{
	s = sprt;
	x = s->getX();
	y = s->getY();
	srand(time(NULL));
	currentseq = h;
}

BasicNPC::~BasicNPC()
{
	delete s;
}

void BasicNPC::update()
{
	if (rand() % 2 == 1)
	{
		//move left
		x--;
		s->movex(-1);
	}
	else
	{
		//move right
		x++;
		s->movex(1);
	}
}

void BasicNPC::render()
{
	s->show(currentseq);
}

void BasicNPC::handleEvent(Uint32 e)
{

}
