// Includes:
#include "Sprite.h"
#include "Logger.h"
#include "Vector2D.h"

// Constructor
Sprite::Sprite(SDL_Renderer* renderer, std::string texturePath) {
	// Create surface, Load texture
	SDL_Surface* surface = IMG_Load(texturePath.c_str());
	if (surface == nullptr) { Logger::Warn("Unable to find texture asset at: %i", texturePath); }
	tex = SDL_CreateTextureFromSurface(renderer, surface);

	// Free Surface, set default position
	SDL_FreeSurface(surface);

	// Default size and position assignment
	Resize(16, 16);
}

// Deconstructor
Sprite::~Sprite() {
	SDL_DestroyTexture(tex);
}

void Sprite::Render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, tex, NULL, &tRect);
}

void Sprite::SetPosition(Vector2D position) {
	tRect.x = position.X; tRect.y = position.Y;
}

void Sprite::Resize(int w, int h) {
	tRect.w = w; tRect.h = h;
}