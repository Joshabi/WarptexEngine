#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <SDL.h>
#include <SDL_ttf.h>

class MenuItem {
public:
	MenuItem(const std::string& label, std::function<void()> action) : label(label), action(action) {
	}

	std::string label;
	std::function<void()> action;
};

class Menu {
public:
	Menu(const std::vector<MenuItem>& items);

	void Render();
	void Input(int key, bool isPressed);

private:
	std::vector<MenuItem> items;
	size_t selectedIndex;
	bool menuActive = false;
};

class MenuHandler {
public:
	MenuHandler();

	void SetActiveMenu(Menu* menu);
	Menu* GetActiveMenu() { return activeMenu; }

	void Render();
	void Input(int key, bool isPressed);

private:
	Menu* activeMenu;
	Menu pauseMenu;
};