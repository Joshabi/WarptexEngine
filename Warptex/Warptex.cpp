// ************************************************************ //
//				Warptex: Bullet Hell C++ SDL Game               //
//     The goal of this, is a full functional, scriptable via   //
//     external JSON data, bullet hell game system. This        //
//     project is currently from the ground up the old systems  //
//     and I would like to implement a multiple game window     //
//     gimmick.        By Joshua Wright                         //
// ************************************************************ //

// Includes:
#include <iostream>
#include <SDL.h>
#include "Logger.h"
#include "SDL_mixer.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "EngineScene.h"

Scene scene;

int main(int argc, char* argv[]) {

    Logger::SetPriority(LogPriority::Info);
    Logger::Info("Engine Started");

    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { return 1; } atexit(SDL_Quit);

    // Initialize SDL Mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
        Logger::Critical("Could not initialize SDL Mixer");
        return 2;
    }

    // Initialize SDL Image
    if (IMG_Init(IMG_INIT_PNG) < 0) {
        Logger::Critical("Could not initialize SDL Image");
        return 3;
    }

    if (TTF_Init() < 0) {
        Logger::Critical("Could not initialize SDL TTF");
        return 4;
    }

    // Initialize main window and renderer
    SDL_Window* mainGameWindow = SDL_CreateWindow("Warptex", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, !SDL_WINDOW_RESIZABLE);
    SDL_Renderer* mainRenderer = SDL_CreateRenderer(mainGameWindow, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawBlendMode(mainRenderer, SDL_BLENDMODE_BLEND);
    scene.Init(mainRenderer, mainGameWindow);
    scene.SetActive(true);
    scene.Main();
}