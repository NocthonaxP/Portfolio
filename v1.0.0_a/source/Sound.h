#pragma once

#include <SDL.h>
#include <iostream>
#include <windows.h>
#include "SDL_Mixer.h"

using namespace std;

class Sound {

private:

	Mix_Chunk *wave;
	Mix_Music *music;

public:

	Sound();
	~Sound();

	void load_music(const string &music_path);
	void load_sfx(const string &chunk_path);
	void play_music();
	void play_sfx();
	void sound_manager();
	void pause_music();
	void stop_music();
	void channel_audio_load();
	void destroy();
};