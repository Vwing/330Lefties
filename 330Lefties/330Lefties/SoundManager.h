// NewSound.h

#ifndef NEWSOUND_H
#define NEWSOUND_H

#include "Sound.h"
#include <map>

class SoundManager
{
public:
	SoundManager(){};
	~SoundManager();

	// Set background music
	void setMusic(std::string path);

	// Plays the background music
	void playMusic();

	// Pause the background music
	void pauseMusic();

	// Resume playing the background music
	void resumeMusic();

	// Pause every sound including background music
	void pauseAll();

	// Resume playing all sounds
	void resumeAll();

	// Create a new sound effect
	void createEffect(std::string sound_name, std::string path);

	// Play sound sound effect
	void playEffect(std::string sound_name);

	// Pause the sound effect - Will only pause the channel if sound is playing
	void pauseEffect(std::string sound_name);

	// Resume playing the sound effect
	void resumeEffect(std::string sound_name);

	// Increase the music volume by 1 
	void musicVolUp();

	// Decrease the music volume by 1
	void musicVolDown();

	// Set the music volume, 0 - 128
	void musicVolSet(int volume);

	// Increase the effect volume by 1
	void effectVolUp(std::string sound_name);

	// Decrease the effect volume by 1
	void effectVolDown(std::string sound_name);

	// Set the effect volume, 0 - 128
	void effectVolSet(std::string sound_name, int volume);

	// Stops all sounds that are currently playing
	void haltAll();

	// Stops the sound while playing
	void halt(std::string sound_name);

private:
	std::map<std::string, Sound*> sounds;  // All effects are stored here
	Sound *music;						  // The background music
	int channels = 0;
};

#endif 