#pragma once
#include "Input.h"
#include "Window.h"

class Game
{
public:
	Game() = default;
	Game(Window* window) { m_window = window; }
	~Game() = default;

	void Init();
	void Update();

	void ShowFPS();

	inline bool QuitGame() { return m_quitGame; }

private:
	Window* m_window = nullptr;
	bool m_quitGame = false;
	Input m_input;

};

