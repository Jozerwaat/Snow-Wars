#pragma once
#include "Window.h"
#include "Vec.h"

class ScoreController
{
public:
	static ScoreController& Instance();

	const int GetScore() { return m_score; }

	void AddScore(int amount);

	void Reset();

	void DisplayScore(vec2 position);
private:
	int m_score;
};

