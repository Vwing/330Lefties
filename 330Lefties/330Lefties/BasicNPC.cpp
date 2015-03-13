#pragma once
#include "BasicNPC.h"
#include "random"
#include "time.h"

BasicNPC::BasicNPC(Sprite* sprt,std::string seq)
{
	s = sprt;
	x = s->getX();
	y = s->getY();
	srand(time(NULL));
	currentseq = seq;

	Unit::enableAI = true;
	Unit::enablePhysics = true;

	body.xPos = x;
	body.yPos = y;
	ai = Unit::createAI(x, y);
	if (ai == nullptr)
	{
		std::cout << "AI failed" << std::endl;
	}
	ai->patrol(1, -2, 40);
}

BasicNPC::~BasicNPC()
{
	delete s;
	delete ai;
}

void BasicNPC::update()
{
	ai->update();
	body.xPos = ai->getX();
	body.yPos = ai->getY();
	s->body.xPos = body.xPos;
	s->body.yPos = body.yPos;
	s->body.screenX = body.screenX;
	s->body.screenY = body.screenY;
	s->body.layer = body.layer;
	//std::cout << "NPC: " <<body.xPos << " " << body.yPos << std::endl;
}

void BasicNPC::render()
{
	s->render();
	//std::cout << s->getX() << " " << s->getY() << std::endl;
}

void BasicNPC::handleEvent(Uint32 e)
{

}

void BasicNPC::move(int x, int y)
{
	BasicNPC::x += x;
	BasicNPC::y += y;
	s->setPos(BasicNPC::x, BasicNPC::y);

}
