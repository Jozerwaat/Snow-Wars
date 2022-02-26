#include <iostream>
#include "MenuController.h"
#include "Button.h"
#include <SDL.h>
#include "Input.h"
#include "Vec.h"

static Button startButton;
static Button quitButton;
static Button fullScreenButton;
static Game* game;
static bool mouseReleased = true;
static Window* wind;

void StartGame()
{
	std::cout << "Game started! " << std::endl;
	startButton.Hide();
	quitButton.Hide();
	fullScreenButton.Hide();

	game->Reset();
}
void QuitGame()
{
	game->Shutdown();
	SDL_Quit();
}
void FullScreen()
{
	game->FullScreen();
	startButton.SetPosition(vec2(wind->GetWidth() / 2, (wind->GetHeight() / 2) - 60));
	quitButton.SetPosition(vec2(wind->GetWidth() / 2, (wind->GetHeight() / 2) + 60));
	fullScreenButton.SetPosition(vec2(wind->GetWidth() - 100, 100));

}
MenuController::MenuController(Window* window, Game* gam)
{
	wind = window;
	game = gam;
	m_window = window;
	startButton = Button(vec2(window->GetWidth() / 2, (window->GetHeight() / 2) - 60), "assets/StartButton.tga", 2);
	quitButton = Button(vec2(window->GetWidth() / 2, (window->GetHeight() / 2) + 60), "assets/QuitButton.tga", 2);
	fullScreenButton = Button(vec2(window->GetWidth() - 100, 100), "assets/FullscreenButton.png", 2);
	startButton.function = StartGame;
	quitButton.function = QuitGame;
	fullScreenButton.function = FullScreen;
}

void MenuController::Show()
{
	startButton.Show();
	quitButton.Show();
	fullScreenButton.Show();
}

void MenuController::Update()
{
	startButton.Update();
	quitButton.Update();
	fullScreenButton.Update();
}



