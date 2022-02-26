#include <string>
#include "ScoreController.h"
#include "Text.h"

static Text scoreText("Assets/GameFont.TTF", 50, "Score: 0", { 0,100,255,255 });

ScoreController& ScoreController::Instance()
{
	static ScoreController s;
	return s;
}

void ScoreController::AddScore(int amount)
{
	m_score += amount;
	scoreText.ChangeText("Score: " + std::to_string(m_score));
}

void ScoreController::Reset()
{
	m_score = 0;
	AddScore(0);
}

void ScoreController::DisplayScore(vec2 position)
{
	std::string scoreString = "Score: " + std::to_string(m_score);
	char scoreChar[11];
	//strcpy(scoreChar, scoreString.c_str());
	//screen->Print(scoreChar, 10, 10, 0xffff0000, 3);
	scoreText.Display(position);
}
