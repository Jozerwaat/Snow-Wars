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

	void Update();
	void Show();

private:
	Window* m_window;
	Game m_game;
};
