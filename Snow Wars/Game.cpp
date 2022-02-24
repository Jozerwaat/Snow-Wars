#include <string>
#include <iostream>
#include "Game.h"
#include "Timer.h"
#include "Text.h"
#include "Sprite.h"

static const Text fpsText("Assets/GameFont.TTF", 40, "FPS: ", { 255,0,0,255 });

Sprite mouse(vec2(100, 100), vec2(10, 10), "Assets/Cursor.png");
Text text("Assets/GameFont.TTF", 40, "Test message", { 255,0,0,255 });


void Game::Update()
{
	if(m_input.QuitGame())
		m_quitGame = true;

	mouse.Draw(m_input.GetMousePos());
	text.Display(vec2(10, 10));
	m_input.Update();
	Timer::Instance().Tick();
	ShowFPS();
}

void Game::ShowFPS()
{
	std::string fpsString = std::to_string(Timer::Instance().GetFPS());
	char fpsChar[11];
	strcpy_s(fpsChar, fpsString.c_str());
	std::cout << "FPS: " << fpsString << std::endl;
	//m_screen->Print(fpsChar, m_screen->GetWidth() - 60, 10, 0xffff0000, 3);
}
