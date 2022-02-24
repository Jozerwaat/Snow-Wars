#include "Window.h"
#include "Sprite.h"
#include "Text.h"
#include "Input.h"

int main(int argc, char** argv)
{
	Window window("Snow Wars", 800, 600);

	Sprite mouse(vec2(100, 100), vec2(10, 10), "Assets/Cursor.png");
	Text text("Assets/GameFont.TTF", 40, "Test message", { 255,0,0,255 });
	Input input;

	while (window.IsClosed() == false) 
	{
		window.Render();
		mouse.Draw(input.GetMousePos());
		text.Display(vec2(10, 10));
		input.Update();

		if (input.QuitGame())
			window.Close();
	}
	return 0;
}