#pragma once

// ******************************** //
//  Component for objects that can  //
//  allow them to display sprites   //
//  on the screen via Surfaces.     //
// ******************************** //

// Includes:
#include "SDL.h"
#include "SDL_image.h"
#include <string>

class Sprite {
public:
	Sprite(SDL_Renderer* renderer, std::string texturePath);
	~Sprite();

	void Render(SDL_Renderer* renderer);
	void SetPosition(int x, int y);  // Set via coords
	void Resize(int w, int h); // Set via width and height

private:
	SDL_Rect tRect;
	SDL_Texture* tex;
};