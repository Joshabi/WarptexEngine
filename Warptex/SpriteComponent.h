#pragma once

// Includes:
#include "GCS.h"
#include "Components.h"
#include "TextureHandler.h"
#include "SDL.h"
#include "SDL_image.h"
#include "Vector2D.h"
#include "Logger.h"

class SpriteComponent : public Component
{
public:
	// Default Constructor
	// Construct Sprite given Texture Path
	SpriteComponent() = default;
	SpriteComponent(SDL_Renderer* renderer, std::string texturePath) {
		usingHandler = false;
		SetTexture(renderer, texturePath);

		int queryResult = SDL_QueryTexture(tex, nullptr, nullptr, &tRect.w, &tRect.h);
		if (queryResult != 0) {
			Logger::Warn("Unable to query texture: %i, defaulting to 16x16", texturePath);
			Resize(16, 16);
		}
		Init();
	}

	// Construct Sprite given Texture ID
	SpriteComponent(SDL_Renderer* renderer, int TexID) {
		usingHandler = true;
		SetTexture(renderer, TexID);

		int queryResult = SDL_QueryTexture(tex, nullptr, nullptr, &tRect.w, &tRect.h);
		if (queryResult != 0) {
			Logger::Warn("Unable to query texture: %i, defaulting to 16x16", TexID);
			Resize(16, 16);
		}
		Init();
	}

	// Destruct Sprite
	~SpriteComponent() {
		if (usingHandler == false) {
			SDL_DestroyTexture(tex);
		}
	}

	void Init() override {
		// If the parent object has a transform component, use it, else make a new one and attatch it
		if (!parentObject->HasComponent<TransformComponent>()) {
			parentObject->AddComponent<TransformComponent>();
		}
		transform = &parentObject->GetComponent<TransformComponent>();
	}

	// Modify this objects texture via TextureHandler
	void SetTexture(SDL_Renderer* renderer, int TexID) {
		// Destroy old texture if not using TextureHandler
		if (!usingHandler) {
			SDL_DestroyTexture(tex);
			usingHandler = true;
		}

		// Set new texture
		tex = TextureHandler::Inst(renderer).GetTexture(TexID);
		if (tex == nullptr) {
			Logger::Warn("Texture not found, Invalid Tex ID: %i", TexID);
		}
	}

	// Modify this objects texture via new texture path
	void SetTexture(SDL_Renderer* renderer, std::string texturePath) {
		if (!usingHandler) {
			SDL_DestroyTexture(tex);
		}

		SDL_Surface* surface = IMG_Load(texturePath.c_str());
		if (surface == nullptr) { Logger::Warn("Unable to find texture asset at: %i", texturePath); }
		tex = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
	}

	// Render Sprite to given Renderer
	void Render(SDL_Renderer* renderer) override {
		SDL_RenderCopy(renderer, tex, NULL, &tRect);
	}

	SDL_Rect GetRect() { return tRect; }
	void SetPosition(Vector2D position) { tRect.x = position.X; tRect.y = position.Y; }
	void Resize(int w, int h) { tRect.w = w; tRect.h = h; transform->SetSize(w, h); }
	void SetOpacity(int opacity) {
		opacity = std::min(std::max(opacity, 0), 255);
		if (SDL_SetTextureAlphaMod(tex, opacity) != 0) {
			Logger::Error("SDL_SetTextureAlphaMod failed: %s", SDL_GetError());
		}
	}

private:
	SDL_Rect tRect;
	SDL_Texture* tex;
	TransformComponent* transform;
	bool usingHandler = true;
};