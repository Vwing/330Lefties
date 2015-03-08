#pragma once
#include "NPC.h"

class BasicNPC : public NPC
{
public:
	std::string currentseq = "";
	BasicNPC(Sprite* sprite);
	~BasicNPC();
	void update();
	void render();
	void handleEvent(Uint32 e);

private:
	int x;
	int y;
	Sprite* s;
};
