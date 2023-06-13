// Includes:
#include "AudioHandler.h"
#include "Logger.h"

bool AudioHandler::LoadMusic(std::string musicPath) {
	Mix_Music* music = Mix_LoadMUS(musicPath.c_str());
	if (music == nullptr) {
		Logger::Warn("There was an issue loading the music at: %i", musicPath);
		return false;
	}
	else {
		GameMusic.insert({ GameMusic.size(), music });
		return true;
	}
}

bool AudioHandler::LoadSound(std::string soundPath) {
	Mix_Chunk* sound = Mix_LoadWAV(soundPath.c_str());
	if (sound == nullptr) {
		Logger::Error("There was an issue loading the sound at: %i", soundPath);
		return false;
	}
	else {
		SoundEffects.insert({ SoundEffects.size(), sound });
		return true;
	}
}

int AudioHandler::PlaySound(int ID) {
	if (!muted) {
		if (SoundEffects.count(ID) > 0) {
			Mix_PlayChannel(-1, SoundEffects.at(ID), 0);
			return 1;
		}
		else {
			Logger::Error("Invalid Sound ID, %i", ID);
			return -1;
		}
	}
	return 0;
}

int AudioHandler::PlayMusic(int ID, float duration) {
	if (!muted) {
		if (GameMusic.count(ID) > 0) {
			Mix_PlayMusic(GameMusic.at(ID), duration);
			return 1;
		}
		else {
			Logger::Error("Invalid Music ID, %i", ID);
			return -1;
		}
	}
	return 0;
}

AudioHandler::~AudioHandler() {

}

AudioHandler::AudioHandler() {
	LoadSound(PROJ_FIRED);
	LoadSound(PLAYER_HIT);
}