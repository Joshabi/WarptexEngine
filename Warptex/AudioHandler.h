#pragma once

// Includes:
#include <map>
#include <string>
#include "SDL_mixer.h"

constexpr auto PLAYER_HIT = "./Assets/Audio/Sounds/Player_Hit.wav";
constexpr auto PROJ_FIRED = "./Assets/Audio/Sounds/Projectile_Fire.wav";

/// <summary>
/// Handles the music and sound effects for the engine
/// </summary>
class AudioHandler {
public:
	static AudioHandler& Inst() {
		static AudioHandler inst;
		return inst;
	}

	std::map<int, Mix_Chunk*> SoundEffects;
	std::map<int, Mix_Music*> GameMusic;

	int PlayMusic(int ID, float duration = -1);
	int PlaySound(int ID);

	bool LoadMusic(std::string musicPath);
	bool LoadSound(std::string soundPath);

	bool IsMuted() {
		return muted;
	}

	void Mute(bool value) {
		muted = value;
	}

private:
	AudioHandler();
	~AudioHandler();

	bool muted = false;
};