#pragma once
#include "game.h"
#include "Input.h"
#include "Window.h"
#include "Game.h"

class MenuController
{
public:
	MenuController() = default;

	MenuController(Window* window, Game* game);
	~MenuController() = default;

	void Update();
	void ShowPauseScreen();

private:
	Window* m_window = nullptr;
	Game m_game;
};

