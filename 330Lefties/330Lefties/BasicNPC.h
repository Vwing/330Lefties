#pragma once
#include "NPC.h"

class BasicNPC : public NPC
{
public:
	std::string currentseq = "";
	BasicNPC(Sprite* sprite, std::string h);
	~BasicNPC();
	void move(int x, int y);

	void update();
	void render();
	void handleEvent(Uint32 e);


private:
	int x;
	int y;
	Sprite* s;
	AI* ai;
};
