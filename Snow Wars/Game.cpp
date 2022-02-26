#include <string>
#include <iostream>
#include "Game.h"
#include "Timer.h"
#include "Sprite.h"
#include "Text.h"
#include "Renderer.h"
#include "MenuController.h"
#include "SnowballController.h"
#include "Player.h"
#include "Mouse.h"
#include "EnemySpawner.h"

static Window window("Snow Wars", 1920, 1080);

static const Input& input = Input::Instance();

MenuController menuController;
SnowballController snowballController(window);
EnemySpawner enemySpawner;

Player player(vec2(window.GetWidth() / 2, window.GetHeight() / 2), "Assets/Snowman.png", 1);
Mouse mouse(vec2(0, 0), "Assets/Cursor.png", 1);
Text gameTitle("Assets/GameFont.TTF", 100, "Snow Wars", { 0,200,255,255 });

Renderer healthbar("Assets/Healthbar.tga", 4);
Renderer backgroundRend("Assets/BackgroundHD.png", 1);

void Game::Init()
{
	menuController = MenuController(&window, this);
	player.Init(snowballController);
	player.SetHealth(3);
	healthbar.SetFrame(player.GetHealth());
	enemySpawner.Init(window, &player, &snowballController);
}

void Game::Update()
{
	window.Render();
	backgroundRend.Render(vec2(window.GetWidth() / 2, window.GetHeight() / 2));
	menuController.Update();
	input.Instance().Update();
	mouse.Update();

	if (input.Instance().QuitGame())
		m_quitGame = true;


	if (m_gameOver)
		return;

	if (player.GetHealth() <= 0)
	{
		GameOver();
		return;
	}
	healthbar.SetFrame(player.GetHealth());
	healthbar.Render(vec2(window.GetWidth() - 145, window.GetHeight() - 45));

	Timer::Instance().Tick();

	snowballController.UpdateSnowballs();
	player.Update();
	enemySpawner.Update();
	//gameTitle.Display(vec2((window.GetWidth() / 2) -250, 100));
	//ShowFPS();


}

void Game::Reset()
{
	if (m_gameOver == false)
		return;

	Timer::Instance().Reset();
	player.SetHealth(3);
	m_gameOver = false;
}

void Game::GameOver()
{
	//scoreController.Instance().Reset();
	healthbar.SetFrame(0);
	menuController.Show();
	enemySpawner.PoolAll();
	m_gameOver = true;
}

void Game::Shutdown()
{
	m_quitGame = true;
}

void Game::ShowFPS()
{
	std::string fpsString = std::to_string(Timer::Instance().GetFPS());
	char fpsChar[20];
	strcpy_s(fpsChar, fpsString.c_str());
	std::cout << "FPS: " << fpsString << std::endl;
}
