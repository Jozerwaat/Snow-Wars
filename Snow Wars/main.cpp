#include "Window.h"
#include "Game.h"

int main(int argc, char** argv)
{
	Game game;

	game.InitSpawnedEnemy();

	while (game.QuitGame() == false) 
		game.Update();
	
	return 0;
}