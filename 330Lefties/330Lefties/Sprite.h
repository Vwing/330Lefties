#pragma once

#include "GameObject.h"
#include <vector>
#include <map>

class Sprite : public GameObject
{
public:
	Sprite(int width, int height, SDL_Renderer* ren, int xPos= 0, int yPos = 0, std::string start_seq = "");
	~Sprite(void);

	void setPos(int x, int y);
	void movex(int delta);
	void movey(int delta);
	int getX();
	int getY();

	// makeFrame returns the unique index of the frame
	int makeFrame(SDL_Texture* texture, int x, int y);

	// addFrameToSequence returns the number of frames in the sequence after the add
	int addFrameToSequence(std::string seqName, int frameIndex);

	// show(int) renders the frame with the specified frameIndex
	void show(int frameIndex);
	// show(string) cycles through all frames in the specified sequence, one per call
	void show(std::string sequence);
	void changeSequence(std::string seq);

	virtual void handleEvent(SDL_Event sdlEvent);
	virtual void update();
	virtual void render();


	// The private part of the class is given as a hint or suggestion.
	// In homework 3 you can make any modifications you want to the class's innards.
protected:
	//int width, height;
	//int currX, currY;		// the coordinates of the sprite's upper left hand corner relative to the window
	SDL_Renderer* renderer;
	std::string current_seq;

	struct frame
	{
		SDL_Texture* texture;
		int x;
		int y;
	};
	std::vector<frame> frames;

	std::map<std::string, std::pair <std::vector<int>, unsigned int>> sequenceList;

};

