// Sound.cpp

#include "Sound.h"

Sound::Sound()
{}

Sound::Sound(std::string path, bool is_effect)
{
	my_path = path;
	if (is_effect)
	{
		music = NULL;
		effect = Mix_LoadWAV(path.c_str());
		if (effect == NULL)
		{
			yikes(("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError()));
		}
	}
	else
	{
		effect = NULL;
		music = Mix_LoadMUS(path.c_str());
		if (music == NULL)
		{
			yikes(("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError()));
		}
	}
}

Sound::~Sound()
{
	if (music != NULL)
	{
		Mix_FreeMusic(music);
	}
	if (effect != NULL)
	{
		Mix_FreeChunk(effect);
	}
	Mix_Quit();
}

void Sound::yikes(std::string message)
{
	std::ostringstream errMsg;
	errMsg << "message: " << message << std::endl;
	OutputDebugString(errMsg.str().c_str());
	std::cout << message << std::endl;
	printf(message.c_str());

	Mix_Quit();
	getchar();
	exit(1);
}

void Sound::setPath(std::string path, bool is_clip)
{
	my_path = path;
	if (is_clip)
	{
		music = NULL;
		effect = Mix_LoadWAV(path.c_str());
		if (effect == NULL)
		{
			yikes(("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError()));
		}
	}
	else
	{
		effect = NULL;
		music = Mix_LoadMUS(path.c_str());
		if (music == NULL)
		{
			yikes(("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError()));
		}
	}
}

void Sound::play()
{
	if (music != NULL)
	{
		// If there is no music playing
		if (Mix_PlayingMusic() == 0)
		{
			// Play the music
			if (Mix_PlayMusic(music, -1) == -1)
			{
				yikes(("Failed to play music! SDL_mixer Error: %s\n", Mix_GetError()));
			}
		}
	}
	if (effect != NULL)
	{
		if (Mix_Playing(my_channel) == 0)
		{
			// Play sound effect
			if (Mix_PlayChannel(my_channel, effect, 0) == -1)
			{
				yikes(("Failed to play effect! SDL_mixer Error: %s\n", Mix_GetError()));
			}
		}
	}
}

void Sound::playInterupt()
{
	if (Mix_Playing(my_channel) == 1)
	{
		Mix_HaltChannel(my_channel);
		my_channel = Mix_PlayChannel(my_channel, effect, 0);
		if (my_channel == -1)
		{
			yikes(("Failed to play effect! SDL_mixer Error: %s\n", Mix_GetError()));
		}
	}
	else
	{
		if (Mix_PlayChannel(my_channel, effect, 0) == -1)
		{
			yikes(("Failed to play effect! SDL_mixer Error: %s\n", Mix_GetError()));
		}
	}
}

void Sound::setChannel(int channel)
{
	my_channel = channel;
	my_volume = Mix_Volume(my_channel, -1);
}

int Sound::getChannel()
{
	return my_channel;
}

int Sound::getVolume()
{
	return my_volume;
}

void Sound::volume(int vol, bool all_sounds)
{
	if (vol < 0)
	{
		my_volume = 0;
	}
	else if (vol > 128)
	{
		my_volume = 128;
	}
	else
	{
		my_volume = vol;
	}
	
	if (all_sounds)
	{
		Mix_Volume(-1, my_volume);
	}
	else if (music != NULL)
	{
		Mix_VolumeMusic(my_volume);
	}
	else if (effect != NULL)
	{
		Mix_VolumeChunk(effect, my_volume);
	}
	
}

void Sound::pause(bool all_sounds)
{
	if (all_sounds)
	{
		Mix_Pause(-1);
	}
	else if (music != NULL)
	{
		Mix_PauseMusic();
	}
	else if (effect != NULL)
	{
		Mix_Pause(my_channel);
	}
}

void Sound::resume(bool all_sounds)
{
	if (all_sounds)
	{
		Mix_Resume(-1);
	}
	else if (music != NULL)
	{
		Mix_ResumeMusic();
	}
	else if (effect != NULL)
	{
		Mix_Resume(my_channel);
	}
}

// Halt the playing of this sound or all sounds by passing true
void Sound::halt(bool all_sounds)
{
	if (all_sounds)
	{
		Mix_HaltChannel(-1);
	}
	else if (music != NULL)
	{
		//Mix_HaltMusic();
		Mix_HaltChannel(0);  // Halt music is not working for some reason
	}
	else if (effect != NULL)
	{
		Mix_HaltChannel(my_channel);
	}
}



