// Sound.cpp

#include "Sound.h"

Sound::Sound()
{

}

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
}

void Sound::yikes(std::string message)
{
	//std::ostringstream errMsg;
	//errMsg << "message: " << message << std::endl;
	//OutputDebugString(errMsg.str().c_str());
	//std::cout << message << std::endl;
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
		if (Mix_Playing(1) == 0)
		{
			// Play sound effect
			get_channel = Mix_PlayChannel(my_channel, effect, 0);
			if (get_channel == -1)
			{
				yikes(("Failed to play effect! SDL_mixer Error: %s\n", Mix_GetError()));
			}
		}

		//if (my_channel == -1)
		//{
		//	// Play sound effect
		//	my_channel = Mix_PlayChannel(-1, effect, 0);
		//	if (my_channel == -1)
		//	{
		//		exit(1);
		//	}
		//}
		//else if (Mix_Playing(my_channel) == 0)
		//{
		//	// Play sound effect
		//	my_channel = Mix_PlayChannel(-1, effect, 0);
		//	if (my_channel == -1)
		//	{
		//		exit(1);
		//	}
		//}
	}
}

void Sound::playInterupt()
{
	if (Mix_Playing(1) == 1)
	{
		Mix_HaltChannel(1);
		get_channel = Mix_PlayChannel(my_channel, effect, 0);
		if (get_channel == -1)
		{
			yikes(("Failed to play effect! SDL_mixer Error: %s\n", Mix_GetError()));
		}
	}
	else
	{
		get_channel = Mix_PlayChannel(my_channel, effect, 0);
		if (get_channel == -1)
		{
			yikes(("Failed to play effect! SDL_mixer Error: %s\n", Mix_GetError()));
		}
	}
}

void Sound::setChannel(int channel)
{
	my_channel = channel;
	get_channel = channel;
}

int Sound::getChannel()
{
	return my_channel;
}

void Sound::volume(int vol)
{
	if (music != NULL)
	{
		Mix_VolumeMusic(vol);
	}
	else if (effect != NULL)
	{
		Mix_VolumeChunk(effect, vol);
	}
}




