#include <string>
#include <iostream>
#include "Game.h"
#include "Timer.h"
#include "Sprite.h"
#include "Text.h"
#include "Renderer.h"
#include "SnowballController.h"
#include "Player.h"
#include "Mouse.h"

static Window window("Snow Wars", 1920, 1080);
static const Input& input = Input::Instance();

SnowballController snowballController(window);
Player player(vec2(window.GetWidth() / 2, window.GetHeight() / 2), vec2(100, 100), "Assets/Snowman.png");
Mouse mouse(vec2(0,0),vec2(50,50),"Assets/Cursor.png");

//Text fpsText("Assets/GameFont.TTF", 40, "Snow Wars", { 255,0,0,255 });

//Renderer cursor(vec2(50, 50), "Assets/Cursor.png");
Renderer backgroundRend(vec2(1920, 1080), "Assets/BackgroundHD.png");

void Game::Init()
{
	player.Init(snowballController);
}

void Game::Update()
{
	window.Render();
	backgroundRend.Render(vec2(window.GetWidth() / 2, window.GetHeight() / 2));

	Timer::Instance().Tick();

	input.Instance().Update();
	snowballController.UpdateSnowballs();
	player.Update();
	mouse.Update();

	//ShowFPS();

	if (input.Instance().QuitGame())
		m_quitGame = true;
}

void Game::ShowFPS()
{
	std::string fpsString = std::to_string(Timer::Instance().GetFPS());
	char fpsChar[11];
	strcpy_s(fpsChar, fpsString.c_str());
	std::cout << "FPS: " << fpsString << std::endl;
}
