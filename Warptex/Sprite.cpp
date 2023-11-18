// Includes:
#include "Sprite.h"
#include "Logger.h"
#include "Vector2D.h"
#include "TextureHandler.h"

// Constructor
Sprite::Sprite(SDL_Renderer* renderer, std::string texturePath) {
	usingHandler = false;
	// Create surface, Load texture
	SDL_Surface* surface = IMG_Load(texturePath.c_str());
	if (surface == nullptr) { Logger::Warn("Unable to find texture asset at: %i", texturePath); }
	tex = SDL_CreateTextureFromSurface(renderer, surface);

	// Free Surface, set default position
	SDL_FreeSurface(surface);

	// Default size and position assignment
	Resize(16, 16);
}

Sprite::Sprite(SDL_Renderer* renderer, int TexID) {
	// Attempt to load a texture from the handler, and in its absence,
	// load the error texture file or set sprite to nullptr essentially.
	usingHandler = true;
	tex = TextureHandler::Inst(renderer).GetTexture(TexID);
	if (tex == nullptr) {
		usingHandler = false;
		Logger::Warn("Texture not found, Invalid Tex ID: %i", TexID);
		SDL_Surface* surface = IMG_Load("./Assets/Core/ErrorTex.png");
		if (surface == nullptr) { Logger::Warn("Unable to find texture asset at: %i", "./Assets/Core/ErrorTex.png"); }
		tex = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
	}

	int queryResult = SDL_QueryTexture(tex, nullptr, nullptr, &tRect.w, &tRect.h);
	if (queryResult != 0) {
		Logger::Warn("Unable to query texture: %i, defaulting to 16x16", TexID);
		Resize(16, 16);
	}
}

// Deconstructor
Sprite::~Sprite() {
	if (usingHandler == false) {
		SDL_DestroyTexture(tex);
	}
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

void Sprite::SetOpacity(int opacity) {
	opacity = std::min(std::max(opacity, 0), 255);
	if (SDL_SetTextureAlphaMod(tex, opacity) != 0) {
		// Handle error, print an error message, etc.
		Logger::Error("SDL_SetTextureAlphaMod failed: %s", SDL_GetError());
	}
}