#include "Window.h"
#include "Rect.h"

int main(int argc, char** argv)
{
	Window window("Snow Wars", 800, 600);
	Rect rect(vec2(100, 100), vec2(10, 10), "Assets/Snowman.png");

	while (window.IsClosed() == false) 
	{
		window.PollEvents();
		window.Clear();
		rect.Draw();
	}
	return 0;
}