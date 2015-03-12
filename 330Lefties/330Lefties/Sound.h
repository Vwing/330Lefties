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

	// Set is_clip to false to load background music
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

	// Returns the current volume for this channel
	int getVolume();

	// Set the volume of the sound from 0 - 128. Pass true for all volume
	void volume(int vol, bool all_sounds = false);

	// Pause the sound on this channel or pass true to pause all
	void pause(bool all_sounds = false);

	// Resume the sound on this channel or pass true to resume all
	void resume(bool all_sounds = false);

	// Halt the playing of this sound or all sounds by passing true
	void halt(bool all_sounds = false);

private:
	// Error message function
	void yikes(std::string message);

	Mix_Music *music = NULL;
	Mix_Chunk *effect = NULL;
	std::string my_path = "";
	int my_channel = -1;
	int my_volume = 64;
};

#endif