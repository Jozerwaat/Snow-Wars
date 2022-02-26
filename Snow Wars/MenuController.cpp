#include <iostream>
#include "MenuController.h"
#include "Button.h"
#include <SDL.h>
#include "Input.h"
#include "Vec.h"

static Button startButton;
static Button quitButton;
static Game* game;
static bool mouseReleased = true;

void StartGame()
{
	std::cout << "Game started! " << std::endl;
	startButton.Hide();
	quitButton.Hide();
	game->Reset();
}
void QuitGame()
{
	game->Shutdown();
	SDL_Quit();
}
MenuController::MenuController(Window* window, Game* gam)
{
	game = gam;
	m_window = window;
	startButton = Button(vec2(window->GetWidth() / 2, (window->GetHeight() / 2) - 60), "assets/StartButton.tga", 2);
	quitButton = Button(vec2(window->GetWidth() / 2, (window->GetHeight() / 2) + 60), "assets/QuitButton.tga", 2);
	startButton.function = StartGame;
	quitButton.function = QuitGame;
}

void MenuController::Show()
{
	startButton.Show();
	quitButton.Show();
}

void MenuController::Update()
{
	startButton.Update();
	quitButton.Update();
}



