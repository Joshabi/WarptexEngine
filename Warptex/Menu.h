#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Sprite.h"
#include "EngineScene.h"

// Forward declaration
class MenuHandler;

class MenuItem {
public:
	MenuItem(const std::string& label, std::function<void()> action) : label(label), action(action) {
	}

	std::string label;
	std::function<void()> action;
};

class Menu {
public:
	Menu(const std::vector<MenuItem>& items, MenuHandler* menuHandler);

	void Render();
	void Input(int key, bool isPressed);

private:
	std::vector<MenuItem> items;
	size_t selectedIndex;
	bool menuActive = false;

	Sprite* menuSprite;
	MenuHandler* parentHandler;
};

class MenuHandler {
public:
	MenuHandler(Scene* scene);
	Scene* parentScene;

	void SetActiveMenu(Menu* menu);
	Menu* GetActiveMenu() { return activeMenu; }

	void Render();
	void Input(int key, bool isPressed);

	Menu pauseMenu;
private:
	Menu* activeMenu;
};