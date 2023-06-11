#pragma once

// ******************************** //
//  A base scene with game loop.    //
//  Handles rendering, input and    //
//  updating GameObjects.           //
// ******************************** //

// Includes:
#include <vector>
#include "SDL.h"
#include "SDL_events.h"
#include "Timer.h"
#include "Gameobject.h"

// Requires GameObject Compiled
class GameObject;

class Scene {
public:
	~Scene();

	SDL_Window* GetWindow() { return gameWindow; }
	SDL_Renderer* GetRenderer() { return gameRenderer; }

	void RegisterGameObject(GameObject* obj);
	void DeregisterGameObject(GameObject* obj);

	void SetActive(bool state);
	void Init(SDL_Renderer* renderer, SDL_Window* _window);
	void Main();
	void Input();
	void Update();
	void Render();
	void Quit();

private:
	SDL_Window* gameWindow;
	SDL_Renderer* gameRenderer;
	Timer mainTimer;
	std::vector<GameObject*> sceneObjects;
	
	float framesElapsed = 0;
	const float delta = 16.6666;
	bool active = false;
};