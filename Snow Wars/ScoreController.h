#pragma once
#include "Window.h"

class ScoreController
{
public:
	static ScoreController& Instance();

	const int GetScore() { return m_score; }

	void AddScore(int amount) { m_score += amount; }

	void Reset() { m_score = 0; }

	void DisplayScore(Window* window);
private:
	int m_score;
};

