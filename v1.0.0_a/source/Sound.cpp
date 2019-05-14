#include "stdafx.h"
#include "Sound.h"

Sound::Sound() {

}


Sound::~Sound() {

}


void Sound::channel_audio_load() {

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 16384) < 0) {
		cout << "Cant open audio: " << Mix_GetError() << endl;
	}

	Mix_AllocateChannels(16);
}


void Sound::load_music(const string &music_path) {

	music = Mix_LoadMUS(music_path.c_str());
	Mix_VolumeMusic(64);
}


void Sound::load_sfx(const string &chunk_path) {

	wave = Mix_LoadWAV(chunk_path.c_str());
	Mix_VolumeChunk(wave, 128);
}


void Sound::play_music() {

	Mix_PlayMusic(music, 1);
}


void Sound::play_sfx() {

	Mix_PlayChannel(3, wave, 0);
}


void Sound::pause_music() {

	if (Mix_PlayingMusic() == 0) {
		Mix_PlayMusic(music, 1);
	}
	else {
		if (Mix_PausedMusic() == 1) {
			Mix_ResumeMusic();
		}
		else {
			Mix_PauseMusic();
		}
	}
}


void Sound::stop_music() {

	Mix_HaltMusic();
}


void Sound::destroy() {

	Mix_FreeChunk(wave);
	Mix_FreeMusic(music);
	Mix_CloseAudio();
}

void Sound::sound_manager() {

	channel_audio_load();
	load_music("res/Fairwind.mp3");
	load_sfx("res/sword.wav");
	

}