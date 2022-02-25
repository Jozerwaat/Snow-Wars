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
#include "EnemySpawner.h"

static Window window("Snow Wars", 1920, 1080);
static const Input& input = Input::Instance();

SnowballController snowballController(window);
Player player(vec2(window.GetWidth() / 2, window.GetHeight() / 2), vec2(100, 100), "Assets/Snowman.png", 1);
Mouse mouse(vec2(0,0),vec2(50,50),"Assets/Cursor.png", 1);
EnemySpawner enemySpawner;

Text gameTitle("Assets/GameFont.TTF", 100, "Snow Wars", { 0,200,255,255 });

//Renderer cursor(vec2(50, 50), "Assets/Cursor.png");
Renderer backgroundRend(vec2(1920, 1080), "Assets/BackgroundHD.png",1);
Renderer startButton(vec2(400, 100), "Assets/StartButton.tga", 2);

void Game::Init()
{
	player.Init(snowballController);
	enemySpawner.Init(window, &player, &snowballController);
}

void Game::Update()
{
	window.Render();
	backgroundRend.Render(vec2(window.GetWidth() / 2, window.GetHeight() / 2));
	startButton.Render(vec2(window.GetWidth() / 2, window.GetHeight() / 2));

	Timer::Instance().Tick();

	input.Instance().Update();
	snowballController.UpdateSnowballs();
	player.Update();
	mouse.Update();
	enemySpawner.Update();
	//gameTitle.Display(vec2((window.GetWidth() / 2) -250, 100));
	//ShowFPS();

	if (input.Instance().QuitGame())
		m_quitGame = true;
}

void Game::ShowFPS()
{
	std::string fpsString = std::to_string(Timer::Instance().GetFPS());
	char fpsChar[20];
	strcpy_s(fpsChar, fpsString.c_str());
	std::cout << "FPS: " << fpsString << std::endl;
}
