
#include "menu.h"

Menu::Menu(const std::vector<MenuItem>& items) : items(items), selectedIndex(0), menuActive(false) { }

void Menu::Render() {

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
		}
	}
};

MenuHandler::MenuHandler() : activeMenu(nullptr),
	pauseMenu({{"Resume", []() { "Execute Option One"; }},
			  {"Quit", []() { "Execute Option Two"; }}}) {
	
}

void MenuHandler::SetActiveMenu(Menu* menu) { activeMenu = menu; }

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