
// Includes:
#include <string>
#include "SDL.h"
#include "EngineScene.h"
#include "Logger.h"

// Deconstructor
Scene::~Scene() {
	// Clean-up scene, de-activated stuff
}

void Scene::SetActive(bool state) {
	active = state;
}

void Scene::Init(SDL_Renderer* renderer, SDL_Window* window) {
	gameRenderer = renderer;
	gameWindow = window;
}

void Scene::Main() {
	Logger::Info("EngineScene Loading");
	Logger::Info("Scene State: %i", active);
	while (active) {
		// Main Engine Loop for standard scene
		mainTimer.Reset();

		Input();
		Update();
		Render();

		// Wait for additional ticks
		if (mainTimer.TicksElapsed() < delta) {
			SDL_Delay(delta - mainTimer.TicksElapsed());
		}
	}
}

void Scene::Input() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT:
			SDL_Quit();
		}
	}
}

void Scene::Update() { }

void Scene::Render() {
	// Clear Renderer
	SDL_RenderClear(gameRenderer);
	SDL_RenderPresent(gameRenderer);
}

// Quits the scene
void Scene::Quit() { Logger::Info("Ending Engine"); }