#include "Window.h"
#include "Game.h"

int main(int argc, char** argv)
{
	Window window("Snow Wars", 1920, 1080);
	Game game;

	while (game.QuitGame() == false) 
	{
		window.Render();
		game.Update();

		//if (input.QuitGame())
			//window.Close();
	}
	return 0;
}