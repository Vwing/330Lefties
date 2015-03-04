#pragma once

#include "GameObject.h"
#include <vector>
#include <map>

class Sprite : public GameObject
{
public:
	Sprite(int width, int height, SDL_Renderer* ren, int xPos = 0, int yPos = 0, std::string start_seq = "");
	~Sprite(void);

	void setPos(int x, int y);
	void movex(int delta);
	void movey(int delta);
	int getX();
	int getY();

	// makeFrame returns the unique index of the frame
	int makeFrame(SDL_Texture* texture, int x, int y);

	// addFrameToSequence returns the number of frames in the sequence after the add
	//int addFrameToSequence(std::string seqName, int frameIndex);
	int addFrameToSequence(std::string seqName, int frameIndex, unsigned int duration = 0);

	// show(int) renders the frame with the specified frameIndex
	void show(int frameIndex);
	// show(string) cycles through all frames in the specified sequence, one per call
	void show(std::string sequence);
	void changeSequence(std::string seq);

	virtual void handleEvent(Uint32 sdlEvent);
	virtual void update();
	virtual void render();

protected:
	SDL_Renderer* renderer;
	std::string current_seq; // The name of the current sequence being displayed. Default is empty string.
	unsigned long long frameStartTime;

	struct frame
	{
		SDL_Texture* texture;
		int x;
		int y;
	};
	// Container for all the frames available to this sprite
	std::vector<frame> frames;

	//frameSequence has a vector of pairs of (1. frameIndex 2. frame duration in milliseconds) and the current index the vector is on
	struct frameSequence{
		std::vector<std::pair<int, unsigned int>> frameVector;
		unsigned int currentIndex;
	};

	std::map<std::string, frameSequence> sequenceList;

	// Mapping of sequence names to pairs of (1. List of frames 2. Current sequence index)
	//std::map<std::string, std::pair <std::vector<int>, unsigned int>> sequenceList;
};

