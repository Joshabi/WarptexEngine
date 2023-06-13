
// Includes:
#include <string>
#include "SDL.h"
#include "EngineScene.h"
#include "Logger.h"
#include "AudioHandler.h"
#include "Player.h"
#include "Projectile.h"

Player* testObject;
Projectile* testProj;

// Deconstructor
Scene::~Scene() {
	// Clean-up scene, de-activated stuff
}

void Scene::RegisterGameObject(GameObject* obj) {
	sceneObjects.push_back(obj);
}

void Scene::DeregisterGameObject(GameObject* obj) {
	sceneObjects.erase(std::remove(sceneObjects.begin(), sceneObjects.end(), obj), sceneObjects.end());
}

void Scene::SetActive(bool state) {
	active = state;
}

void Scene::Init(SDL_Renderer* renderer, SDL_Window* window) {
	gameRenderer = renderer;
	gameWindow = window;

	// Testing Purposes: GameObjects
	testObject = new Player(this);
	RegisterGameObject(testObject);
	testObject->GetTransform().SetPosition(392, 600);

	// Testing Purposes: Projectiles and Collisions
	testProj = new Projectile(this, 1, 1, 2, 0);
	RegisterGameObject(testProj);
	testProj->GetTransform().SetPosition(392, 450);

	// Testing purposes: Audio
	AudioHandler::Inst().PlaySound(0);
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
		// Handle the cases for Scene Keybinds
		switch (e.type) {
		case SDL_QUIT:
			SDL_Quit();
			break;
		case SDL_KEYDOWN:
			if (e.key.keysym.sym > MAX_KEYS) { break; }
			gKeys[e.key.keysym.sym] = true;
			break;
		case SDL_KEYUP:
			if (e.key.keysym.sym > MAX_KEYS) { break; }
			gKeys[e.key.keysym.sym] = false;
			break;
		}
	}

	// Handle GameObject inputs
	for (int i = 0; i < sceneObjects.size(); i++) {
		// For each key:
		for (int key = 0; key < MAX_KEYS; key++) {
			sceneObjects[i]->Input(key, gKeys[key]);
		}
	}
}

void Scene::Update() {
	// Handle GameObject updates
	for (int i = 0; i < sceneObjects.size(); i++) {
		sceneObjects[i]->Update();
	}
}

void Scene::Render() {
	// Clear Renderer
	SDL_RenderClear(gameRenderer);

	// Render Objects
	for (int i = 0; i < sceneObjects.size(); i++) {
		sceneObjects[i]->Render();
	}

	// Present Renderer
	SDL_RenderPresent(gameRenderer);
}

// Quits the scene
void Scene::Quit() { Logger::Info("Ending Engine"); }