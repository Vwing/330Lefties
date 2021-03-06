#ifndef CHARACTER_H
#define CHARACTER_H
#include "Unit.h"
#include "Sprite.h"

class Character : public Unit {
public:
	const static int JUMP_DISTANCE = 50;

	Character(Sprite* sprite, int startHP = 100);
	~Character(void);

	//Increases or decreases HP given int
	void changeHP(int deltaHP);
	int getHP();

	void changeSequenceName(std::string movementType, std::string seq);

	//Moves character the distance given to the function
	void moveLeft(unsigned int distance);
	void moveRight(unsigned int distance);
	void jump(unsigned int distance);
	void jump(unsigned int distance, bool left);
	void fall(unsigned int distance);
	void setPos(int x, int y);

	//void handleEvent(SDL_Event sdlEvent);
	void handleEvent(Uint32 sdlEvent);
	void update();
	void render();

private:
	int hp;
	int mass;
	bool jumping;
	bool falling;
	int currJumpDistance;
	Sprite* sprite;

	struct MoveSequences{
		std::string left;
		std::string right;
		std::string jump;
		std::string fall;
	};
	MoveSequences moveSeq;

};
#endif