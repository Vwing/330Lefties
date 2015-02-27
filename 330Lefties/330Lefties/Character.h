#ifndef CHARACTER_H
#define CHARACTER_H
#include "Sprite.h"

class Character: public Sprite{
public:
	Character(int width, int height, SDL_Renderer* ren, int startX, int startY, std::string start_seq, int startHP = 100);
	~Character(void);

	//Increases or decreases HP given int
	void changeHP(int deltaHP);
	int getHP();

	void changeSequenceName(std::string movementType, std::string seq);

	//Moves character the distance given to the function
	void moveLeft(unsigned int distance);
	void moveRight(unsigned int distance);
	void jump(unsigned int distance);
	void fall(unsigned int distance);

	void handleEvent(SDL_Event sdlEvent);
	void update();
	void render();

private:
	int x;
	int y;
	int hp;
	int mass;

	struct MoveSequences{
		std::string left;
		std::string right;
		std::string jump;
		std::string fall;
	};
	MoveSequences moveSeq;

};
#endif