
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
#include "Menu.h"

Player* testObject;
Projectile* testProj;
RadialSpawner* spawner;
MenuHandler* menuHandler;

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

void Scene::SetPaused(bool state) {
	pauseMenuActive = state;
}

void Scene::Init(SDL_Renderer* renderer, SDL_Window* window) {
	gameRenderer = renderer;
	gameWindow = window;
	windowSurface = SDL_GetWindowSurface(gameWindow);
	menuHandler = new MenuHandler(this);
	grid = new SpatialGridPartition(5,5);

	// Initialization Information for Handlers:
	Logger::Info("Texture Count %i", TextureHandler::Inst(gameRenderer).GameTextures.size());
	Logger::Info("Sound Count %i", AudioHandler::Inst().SoundEffects.size());
	Logger::Info("Music Count %i", AudioHandler::Inst().GameMusic.size());

	// Testing Purposes: GameObjects
	testObject = new Player(this);
	RegisterGameObject(testObject);
	testObject->GetTransform().SetPosition(392, 600);

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

	menuHandler->SetActiveMenu(&menuHandler->pauseMenu);
}

void Scene::Main() {
	Logger::Info("EngineScene Loading");
	Logger::Info("Scene State: %i", active);
	while (active) {
		// Main Engine Loop for standard scene
		mainTimer.Reset(); profilerTimer.Reset();

		Input();
		Logger::Debug("Input: %i ticks", profilerTimer.TicksElapsed());
		profilerTimer.Reset();
		Update();
		Logger::Debug("Update: %i ticks", profilerTimer.TicksElapsed());
		profilerTimer.Reset();
		Render();
		Logger::Debug("Render: %i ticks", profilerTimer.TicksElapsed());

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

	// Handle Input for all keys
	for (int key = 0; key < MAX_KEYS; key++) {
		// Update Game Objects if pause menu not active
		if (!pauseMenuActive) {
			for (int i = 0; i < sceneObjects.size(); i++) {
				sceneObjects[i]->Input(key, gKeys[key]);
			}

			// Pause Game if ESC is pressed
			if (gKeys[SDLK_ESCAPE]) {
				menuHandler->SetActiveMenu(&menuHandler->pauseMenu);
				pauseMenuActive = true;
			}
		}
		// Update Menu
		menuHandler->Input(key, gKeys[key]);
	}
}

void Scene::Update() {
	// Handle GameObject updates
	if (!pauseMenuActive) {
		grid->Update(GetAllGameObjects());

		for (int i = 0; i < sceneObjects.size(); i++) {
			sceneObjects[i]->Update();
		}
	}
}

void Scene::Render() {
	// Clear Renderer
	SDL_RenderClear(gameRenderer);

	// Render Objects
	for (const auto& obj : sceneObjects) {
		obj->Render();
	}

	// Render Menu
	menuHandler->Render();

	// Present Renderer
	SDL_RenderPresent(gameRenderer);
}

// Quits the engine
void Scene::QuitEngine() {
	Logger::Info("Exiting Engine"); 
	SDL_Quit();
	exit(712);
}