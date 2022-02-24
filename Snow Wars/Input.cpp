#include "Input.h"
#include <iostream>

Input::Input()
{
}

Input::~Input()
{
}

void Input::Update()
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_quit = true;
			break;

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				m_quit = true;
				break;
			}
			case SDL_MOUSEMOTION:
				m_mousePos.x = event.motion.x;
				m_mousePos.y = event.motion.y;
				break;

		default:
			break;
		}
	}
}