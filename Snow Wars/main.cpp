#include "Window.h"

int main(int argc, char** argv)
{
	Window window("Snow Wars", 800, 600);

	while (window.IsClosed() == false) 
	{
		window.PollEvents();
		window.Clear();
	}
	return 0;
}