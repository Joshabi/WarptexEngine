// Includes:
#include "TextureHandler.h"
#include "Logger.h"
#include "SDL_image.h"

bool TextureHandler::LoadTexture(std::string texturePath) {
	SDL_Surface* surface = IMG_Load(texturePath.c_str());
	if (surface == nullptr) { Logger::Warn("Unable to find texture asset at %i", texturePath); return false; }
	else {
		SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
		GameTextures.insert({ GameTextures.size(), tex });
		SDL_FreeSurface(surface);
		return true;
	}
}

TextureHandler& TextureHandler::Inst(SDL_Renderer* renderer) {
	static TextureHandler inst(renderer);
	inst.renderer = renderer;
	return inst;
}

SDL_Texture* TextureHandler::GetTexture(int ID) {
	auto iterator = GameTextures.find(ID);
	return (iterator != GameTextures.end()) ? iterator->second : nullptr;
}

TextureHandler::TextureHandler(SDL_Renderer* renderer) : renderer(renderer) {
	LoadTexture(PLAYER_TEX);
	LoadTexture(PROJECTILE_TEX);
}