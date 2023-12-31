#pragma once

// Includes:
#include <map>
#include <string>
#include "SDL.h"

constexpr auto PLAYER_TEX = "./Assets/Artwork/Player.png";
constexpr auto PROJECTILE_TEX = "./Assets/Artwork/Projectile.png";
constexpr auto MENU_FRAME_TEX = "./Assets/Artwork/MenuFrame.png";

/// <summary>
/// Handles sprite loading for the engine
/// </summary>
class TextureHandler {
public:
	static TextureHandler& Inst(SDL_Renderer* renderer);
	std::map<int, SDL_Texture*> GameTextures;

	SDL_Texture* GetTexture(int ID);
	bool LoadTexture(std::string texturePath);
private:
	SDL_Renderer* renderer;
	TextureHandler(SDL_Renderer* renderer);
};