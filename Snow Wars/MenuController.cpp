#include <iostream>
#include "MenuController.h"
#include "Button.h"
#include <SDL.h>
#include "Input.h"
#include "Vec.h"
#include "Text.h"
#include "Window.h"

static Button startButton;
static Button quitButton;
static Button fullScreenButton;

static Button resumeButton;
static Button menuButton;

static Game* game;
static Window* wind;
static bool mouseReleased = true;

Text gameTitle("Assets/GameFont.TTF", 100, "Snow Wars", { 0,200,255,255 });
Renderer overlayRenderer("Assets/Overlay.png", 1);

void StartGame()
{
	std::cout << "Game started! " << std::endl;

	game->Reset();
}
void ResumeGame() 
{
	game->UnPause();
}
void QuitGame()
{
	game->Shutdown();
	SDL_Quit();
}

void ShowMenu() 
{
	game->GameOver();
}
void FullScreen()
{
	game->FullScreen();
	startButton.SetPosition(vec2(wind->GetWidth() / 2, (wind->GetHeight() / 2) - 60));
	quitButton.SetPosition(vec2(wind->GetWidth() / 2, (wind->GetHeight() / 2) + 60));
	resumeButton.SetPosition(vec2(wind->GetWidth() / 2, (wind->GetHeight() / 2) - 60));
	menuButton.SetPosition(vec2(wind->GetWidth() / 2, (wind->GetHeight() / 2) + 60));
	fullScreenButton.SetPosition(vec2(wind->GetWidth() - 100, 100));

	overlayRenderer.~Renderer();
	new(&overlayRenderer) Renderer("Assets/Overlay.png", 1, vec2(wind->GetWidth(), wind->GetHeight()));
}
MenuController::MenuController(Window* window, Game* gam)
{
	wind = window;
	game = gam;
	m_window = window;
	startButton = Button(vec2(window->GetWidth() / 2, (window->GetHeight() / 2) - 60), "assets/StartButton.png", 2);
	quitButton = Button(vec2(window->GetWidth() / 2, (window->GetHeight() / 2) + 60), "assets/QuitButton.png", 2);
	fullScreenButton = Button(vec2(window->GetWidth() - 100, 100), "assets/FullscreenButton.png", 2);
	resumeButton = Button(vec2(window->GetWidth() / 2, (window->GetHeight() / 2) - 60), "assets/ResumeButton.png", 2);
	menuButton = Button(vec2(window->GetWidth() / 2, (window->GetHeight() / 2) + 60), "assets/MenuButton.png", 2);
	
	startButton.function = StartGame;
	resumeButton.function = ResumeGame;
	menuButton.function = ShowMenu;
	quitButton.function = QuitGame;
	fullScreenButton.function = FullScreen;
}

void MenuController::Update()
{
	gameTitle.Display(vec2((m_window->GetWidth() / 2) - 250, 100));

	startButton.Update();
	quitButton.Update();
	fullScreenButton.Update();
}

void MenuController::ShowPauseScreen()
{
	overlayRenderer.Render(vec2(m_window->GetWidth() / 2, m_window->GetHeight() /2));
	
	fullScreenButton.Show();
	resumeButton.Update();
	menuButton.Update();
	fullScreenButton.Update();
}