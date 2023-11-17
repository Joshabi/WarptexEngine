
// Includes:
#include <string>
#include <iostream>
#include <fstream>
#include "SDL.h"
#include "EngineScene.h"
#include "Logger.h"
#include "AudioHandler.h"
#include "TextureHandler.h"
#include "Player.h"
#include "Projectile.h"
#include "RadialSpawner.h"
#include "RadialPattern.h"
#include "SpatialGridPartition.h"

Player* testObject;
Projectile* testProj;
RadialSpawner* spawner;

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
	windowSurface = SDL_GetWindowSurface(gameWindow);
	grid = new SpatialGridPartition(5,5);

	// Initialization Information for Handlers:
	Logger::Info("Texture Count %i", TextureHandler::Inst(gameRenderer).GameTextures.size());
	Logger::Info("Sound Count %i", AudioHandler::Inst().SoundEffects.size());
	Logger::Info("Music Count %i", AudioHandler::Inst().GameMusic.size());

	// Testing Purposes: GameObjects
	testObject = new Player(this);
	RegisterGameObject(testObject);
	testObject->GetTransform().SetPosition(392, 600);

	// Testing Purposes: Projectiles and Collisions
	//testProj = new Projectile(this, 392, 450, 1, 1, 2, 0);
	//RegisterGameObject(testProj);

	// Testing Purposes: Radial Pattern Spawner
	spawner = new RadialSpawner(this, 392, 200);
	RegisterGameObject(spawner);

	// Testing Purposes: Deserializing a Radial Pattern
	std::ifstream inputFile("Assets/Data/Patterns/PatternTest.json");
	if (!inputFile.is_open()) {
		Logger::Error("Failed to open test pattern");
	}
	else {
		Logger::Info("Opened test pattern successfully");
	}

	nlohmann::json jsonPattern;
	try {
		inputFile >> jsonPattern;
	}
	catch (nlohmann::json::parse_error& e) {
		Logger::Error("Failed to parse test pattern");
	}

	RadialPattern pattern;
	from_json(jsonPattern, pattern);

	spawner->ChangePattern(pattern);
	spawner->SetActive(true);
}

void Scene::Main() {
	Logger::Info("EngineScene Loading");
	Logger::Info("Scene State: %i", active);
	while (active) {
		// Main Engine Loop for standard scene
		mainTimer.Reset(); profilerTimer.Reset();

		Input();
		Logger::Info("Input: %i ticks", profilerTimer.TicksElapsed());
		profilerTimer.Reset();
		Update();
		Logger::Info("Update: %i ticks", profilerTimer.TicksElapsed());
		profilerTimer.Reset();
		Render();
		Logger::Info("Render: %i ticks", profilerTimer.TicksElapsed());

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
	grid->Update(GetAllGameObjects());
	
	for (int i = 0; i < sceneObjects.size(); i++) {
		sceneObjects[i]->Update();
	}

	Logger::Info("Scene Objects: %i", sceneObjects.size());
}

void Scene::Render() {
	// Clear Renderer
	SDL_RenderClear(gameRenderer);

	// Render Objects
	for (const auto& obj : sceneObjects) {
		obj->Render();
	}

	// Present Renderer
	SDL_RenderPresent(gameRenderer);
}

// Quits the scene
void Scene::Quit() { Logger::Info("Ending Engine"); }