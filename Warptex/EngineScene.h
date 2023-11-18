#pragma once

// Includes:
#include <vector>
#include "SDL.h"
#include "SDL_events.h"
#include "Timer.h"
#include "Gameobject.h"
#include "nlohmann/json.hpp"
#include "SpatialGridPartition.h"

#define MAX_KEYS (512)

// Requires GameObject Compiled
class GameObject;

/// <summary>
/// Base scene with game loop. Handles rendering, input and updating GameObjects.
/// </summary>
class Scene {
public:
	~Scene();

	SDL_Window* GetWindow() { return gameWindow; }
	SDL_Renderer* GetRenderer() { return gameRenderer; }
	SDL_Surface* GetWindowSurface() { return windowSurface; }
	SpatialGridPartition& GetGrid() { return *grid; }

	void RegisterGameObject(GameObject* obj);
	void DeregisterGameObject(GameObject* obj);
	std::vector<GameObject*> GetAllGameObjects() { return sceneObjects; }

	void SetActive(bool state);
	void SetPaused(bool state);
	Timer* Time() { return &mainTimer; }
	void Init(SDL_Renderer* renderer, SDL_Window* _window);
	void Main();
	void Input();
	void Update();
	void Render();
	void QuitEngine();

private:
	SDL_Window* gameWindow;
	SDL_Renderer* gameRenderer;
	SDL_Surface* windowSurface;
	SpatialGridPartition* grid;
	bool gKeys[MAX_KEYS];

	Timer mainTimer;
	Timer profilerTimer;
	std::vector<GameObject*> sceneObjects;
	
	float framesElapsed = 0;
	const float delta = 16.6666;
	bool active = false;
	bool pauseMenuActive = false;
};