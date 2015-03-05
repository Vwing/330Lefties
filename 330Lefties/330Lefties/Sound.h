// Sound.h

#ifndef SOUND_H
#define SOUND_H

#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "Windows.h"
#include <sstream>
#include <string>
#include <iostream>

class Sound
{
public:
	// Default constructor
	Sound();

	// Destructor
	~Sound();

	// Set is_clip to false to load level music
	Sound(std::string path, bool is_effect = true); 
	
	// Set is_clip to false to load level music
	void setPath(std::string path, bool is_clip = true);   

	// Play the sound without any overlap
	void play();  

	// Play the effect and interupt if it is already playing
	void playInterupt();

	// Select a specific channel to play the effect
	void setChannel(int channel);

	// Returns the current channel this sound is played on
	int getChannel();

	// Set the volume of the sound from 0 - 128
	void volume(int vol);

private:
	// Error message function
	void yikes(std::string message);

	Mix_Music *music = NULL;
	Mix_Chunk *effect = NULL;
	std::string my_path = "";
	int my_channel = -1;
	int get_channel = -1;
};

#endif