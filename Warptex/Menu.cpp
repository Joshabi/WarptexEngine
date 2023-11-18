
#include "menu.h"
#include "Logger.h"

Menu::Menu(const std::vector<MenuItem>& items, MenuHandler* menuHandler) : items(items), selectedIndex(0), menuActive(false) {
	parentHandler = menuHandler;
	menuSprite = new Sprite(parentHandler->parentScene->GetRenderer(), 2);

	menuSprite->SetPosition(Vector2D(0, 0));
	menuSprite->SetOpacity(175);
}

void Menu::Render() {
	// If there is a menu sprite, render it
	if (menuSprite != nullptr) {
		menuSprite->Render(parentHandler->parentScene->GetRenderer());
	}

	// Render menu items
	for (size_t i = 0; i < items.size(); ++i) {
		TTF_Font* font = TTF_OpenFont("Assets/Fonts/Arial.ttf", 24);

		SDL_Color color = { 255, 255, 255 };
		if (i == selectedIndex) {
			color = { 255, 0, 0 };
		}

		SDL_Surface* textSurface = TTF_RenderText_Solid(font, items[i].label.c_str(), color);
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(parentHandler->parentScene->GetRenderer(), textSurface);

		SDL_Rect textRect = {
			menuSprite->GetRect().x + (menuSprite->GetRect().w - textSurface->w) / 2,  // Center horizontally
			menuSprite->GetRect().y + menuSprite->GetRect().h / 3 + static_cast<int>(i * 30),  // 1/3 down from the top
			textSurface->w,
			textSurface->h
		};
		SDL_RenderCopy(parentHandler->parentScene->GetRenderer(), textTexture, nullptr, &textRect);

		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(textTexture);
		TTF_CloseFont(font);
	}
};

void Menu::Input(int key, bool isPressed) {
	if (isPressed) {
		switch (key) {
			case SDLK_w:
			case SDLK_UP: {
				if (selectedIndex > 0) {
					selectedIndex--;
				}
				break;
			}
			case SDLK_s:
			case SDLK_DOWN: {
				if (selectedIndex < items.size() - 1) {
					selectedIndex++;
				}
				break;
			}
			case SDLK_KP_ENTER:
			case SDLK_e:
				items[selectedIndex].action();
		}
	}
};

MenuHandler::MenuHandler(Scene* scene) : activeMenu(nullptr), parentScene(scene),
pauseMenu({ {"Resume", [this]() { this->SetActiveMenu(nullptr); return "Execute Option One"; }},
		   {"Quit", [scene]() { scene->QuitEngine(); }} }, this) {
}

void MenuHandler::SetActiveMenu(Menu* menu) { 
	activeMenu = menu; 
	if (menu == nullptr) {
		Logger::Info("Menu System Disabled");
		parentScene->SetPaused(false);
	}
	else {
		Logger::Info("Changed active menu to %i", menu);
		parentScene->SetPaused(true);
	}
}

void MenuHandler::Render() {
	if (activeMenu) {
		activeMenu->Render();
	}
}

void MenuHandler::Input(int key, bool isPressed) {
	if (activeMenu) {
		activeMenu->Input(key, isPressed);
	}
}