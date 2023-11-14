#pragma once

// Includes:
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "Vector2D.h"

/// <summary>
/// Component that allows an object to display a sprite on the screen
/// </summary>
class Sprite {
public:
	Sprite(SDL_Renderer* renderer, std::string texturePath);
	Sprite(SDL_Renderer* renderer, int TexID);
	~Sprite();

	SDL_Rect GetRect() { return tRect; }

	void Render(SDL_Renderer* renderer);
	void SetPosition(Vector2D position);  // Set via coords
	void Resize(int w, int h); // Set via width and height

private:
	SDL_Rect tRect;
	SDL_Texture* tex;
	bool usingHandler = true;
};