#include <string>
#include "ScoreController.h"

ScoreController& ScoreController::Instance()
{
	static ScoreController s;
	return s;
}

void ScoreController::DisplayScore(Window* window)
{
	std::string scoreString = "Score: " + std::to_string(m_score);
	char scoreChar[11];
	//strcpy(scoreChar, scoreString.c_str());
	//screen->Print(scoreChar, 10, 10, 0xffff0000, 3);
}
