#include "SoundManager.h"

SoundManager::~SoundManager()
{
	// Cleanup pointers to sounds
	for (std::map<std::string, Sound*>::iterator iter = sounds.begin(); iter != sounds.end(); iter++)
	{
		delete iter->second;
	}
	if (music != nullptr)
	{
		delete music;
	}
}

// Set background music
void SoundManager::setMusic(std::string path)
{
	music = new Sound(path, false);
}

// Plays the background music
void SoundManager::playMusic()
{
	music->play();
}

// Pause the background music
void SoundManager::pauseMusic()
{
	music->pause();
}

// Resume playing the background music
void SoundManager::resumeMusic()
{
	music->play();
}

// Pause every sound including background music
void SoundManager::pauseAll()
{
	music->pause(true);
}

// Resume playing all sounds
void SoundManager::resumeAll()
{
	music->resume(true);
}

// Create a new sound effect
void SoundManager::createEffect(std::string sound_name, std::string path)
{
	Sound *effect = new Sound(path);
	sounds[sound_name] = effect;
	channels++;
	effect->setChannel(channels);
}

// Play sound sound effect
void SoundManager::playEffect(std::string sound_name)
{
	sounds[sound_name]->play();
}

// Pause the sound effect - Will only pause the channel if sound is playing
void SoundManager::pauseEffect(std::string sound_name)
{
	sounds[sound_name]->play(); // The effect must be playing on the channel for the channel to pause
	sounds[sound_name]->pause();
}

// Resume playing the sound effect
void SoundManager::resumeEffect(std::string sound_name)
{
	sounds[sound_name]->resume();
}

// Increase the music volume by 1 
void SoundManager::musicVolUp()
{
	music->volume(music->getVolume() + 1);
}

// Decrease the music volume by 1
void SoundManager::musicVolDown()
{
	music->volume(music->getVolume() - 1);
}

// Set the music volume, 0 - 128
void SoundManager::musicVolSet(int volume)
{
	music->volume(volume);
}

// Increase the effect volume by 1
void SoundManager::effectVolUp(std::string sound_name)
{
	sounds[sound_name]->volume(sounds[sound_name]->getVolume() + 1);
}

// Decrease the effect volume by 1
void SoundManager::effectVolDown(std::string sound_name)
{
	sounds[sound_name]->volume(sounds[sound_name]->getVolume() - 1);
}

// Set the effect volume, 0 - 128
void SoundManager::effectVolSet(std::string sound_name, int volume)
{
	sounds[sound_name]->volume(volume);
}

// Stops all sounds that are currently playing
void SoundManager::haltAll()
{
	music->halt(true);
}

// Stops the sound while playing
void SoundManager::halt(std::string sound_name)
{
	sounds[sound_name]->halt();
}