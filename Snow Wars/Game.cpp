#include <string>
#include <iostream>
#include <time.h>
#include "Game.h"
#include "Timer.h"
#include "Renderer.h"
#include "MenuController.h"
#include "SnowballController.h"
#include "ScoreController.h"
#include "PowerupController.h"
#include "ProjectileController.h"
#include "Player.h"
#include "Mouse.h"
#include "EnemySpawner.h"

static Window window("Snow Wars", 1920, 1080);

static const Input& input = Input::Instance();
const static ScoreController& scoreController = ScoreController::Instance();

Player player(&window, vec2((float)window.GetWidth() / 2.0f, (float)window.GetHeight() / 2.0f), "Assets/Snowman.png", 14);

MenuController menuController;
SnowballController snowballController(window);
PowerupController powerupController(&window, &player);
EnemySpawner enemySpawner;
ProjectileController projectileController;

Mouse mouse(vec2(0, 0), "Assets/Cursor.png", 1);

Renderer healthbar("Assets/Healthbar.png", 4);
Renderer backgroundRend("Assets/BackgroundHD.png", 1, vec2((float)window.GetWidth(), (float)window.GetHeight()));

void Game::Init()
{
	projectileController.Instance().Init(window, player);
	srand((unsigned int)std::time(0));
	menuController.~MenuController();
	menuController = MenuController(&window, this);
	player.Init(snowballController);
	player.SetHealth(3);
	healthbar.SetFrame(player.GetHealth());
	enemySpawner.Init(window, &player, &snowballController);
}

void Game::Update()
{
	window.Render();
	backgroundRend.Render(vec2(window.GetWidth() / 2.0f, window.GetHeight() / 2.0f));
	input.Instance().Update();
	scoreController.Instance().DisplayScore(vec2(10.0f, 10.0f));

	if (input.Instance().QuitGame())
		m_quitGame = true;

	if (m_gameOver)
	{
		menuController.Update();
		mouse.Update();
		return;
	}

	if (player.GetHealth() <= 0)
	{
		GameOver();
		return;
	}

	if (input.PauseGame() == false)
		Timer::Instance().Tick();

	healthbar.SetFrame(player.GetHealth());
	healthbar.Render(vec2(window.GetWidth() - 145.0f, window.GetHeight() - 45.0f));

	powerupController.Update();
	snowballController.UpdateSnowballs();
	player.Update();
	enemySpawner.Update();
	projectileController.Instance().Update();

	if (input.PauseGame())
		menuController.ShowPauseScreen();
	
	mouse.Update();
	//ShowFPS();
}

void Game::Reset()
{
	if (m_gameOver == false)
		return;

	Timer::Instance().Reset();
	scoreController.Instance().Reset();

	player.Reset();
	player.GetCollider()->GetTransform()->GetPosition() = vec2(window.GetWidth() / 2.0f, window.GetHeight() / 2.0f);
	m_gameOver = false;
	input.Instance().UnPause();
}

void Game::GameOver()
{
	healthbar.SetFrame(0);
	enemySpawner.PoolAll();
	snowballController.PoolAll();
	projectileController.Instance().PoolAll();
	powerupController.Reset();
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

void Game::FullScreen()
{
	window.Resize();
	backgroundRend.~Renderer();
	new(&backgroundRend) Renderer("Assets/BackgroundHD.png", 1, vec2(window.GetWidth(), window.GetHeight()));
}

void Game::UnPause()
{
	Timer::Instance().Reset();

	input.Instance().UnPause();
}
