#pragma once
#include "Input.h"

class Game
{
public:
	Game() = default;
	~Game() = default;

	void Update();

	void ShowFPS();

	inline bool QuitGame() {return m_quitGame;}

private:
	bool m_quitGame = false;
	Input m_input;

};

