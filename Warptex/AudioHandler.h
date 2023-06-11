#pragma once

// *************************************************** //
//  Handles the music and sound effects for the game,  //
//  made a singleton for access                        //
//  Handles rendering, input and updating GameObjects. //
// *************************************************** //

// Includes:
#include <map>
#include "SDL_mixer.h"
#include "Gameobject.h"

constexpr auto TEST_SOUND_EFFECT = "./Assets/Audio/Sounds/Test.wav";

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