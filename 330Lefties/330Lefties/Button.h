#pragma once

#include "SDL.h"
#include <vector>
#include <map>
#include <functional>


class Button{
public:
	Button(int width, int height, int x, int y, SDL_Renderer* ren, std::string resPath, std::string spritesheet, std::function<void(void)> functocall);
	~Button(void);

	void setPos(int x, int y);
	void logSDLError(std::ostream &os, const std::string &msg);
	int getX();
	int getY();
	SDL_Texture* loadTexture();
	// makeFrame returns the unique index of the frame
	int makeFrame(SDL_Texture* texture, int x, int y);
	// addFrameToSequence returns the number of frames in the sequence after the add
	int addFrameToSequence(std::string seqName, int frameIndex);
	void show(int frameIndex);
	void show(std::string sequence);
	void start(SDL_Event* e);


private:
	int width, height;
	int currX, currY; // location on window
	std::string resPath, spritesheet;
	SDL_Renderer* renderer;
	std::function<void(void)> functocall;
	struct frame
	{
		SDL_Texture* texture;
		int x;
		int y;
	};
	std::vector<frame> frames;

	std::map<std::string, std::vector<int>> sequenceList;
	int sequenceIndex;		// shared by all sequences; it would be better to have
	// one for each sequence
};

