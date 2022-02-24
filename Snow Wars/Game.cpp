#include <string>
#include <iostream>
#include "Game.h"
#include "Timer.h"
#include "Sprite.h"
#include "Text.h"
#include "Renderer.h"

static const Window window("Snow Wars", 1920, 1080);

 Text fpsText("Assets/GameFont.TTF", 40, "Snow Wars", { 255,0,0,255 });

Renderer renderer(vec2(100, 100), "Assets/Cursor.png");
Renderer backgroundRend(vec2(1920, 1080), "Assets/BackgroundHD.png");

void Game::Init()
{

}

void Game::Update()
{
	window.Render();

	if(m_input.QuitGame())
		m_quitGame = true;
	backgroundRend.Render(vec2(window.GetScreenWidth() / 2, window.GetScreenHeight() / 2));

	renderer.Render(m_input.GetMousePos(), 45);
	m_input.Update();
	Timer::Instance().Tick();
	//ShowFPS();
}

void Game::ShowFPS()
{
	std::string fpsString = std::to_string(Timer::Instance().GetFPS());
	char fpsChar[11];
	strcpy_s(fpsChar, fpsString.c_str());
	std::cout << "FPS: " << fpsString << std::endl;
}
