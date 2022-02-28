#include "Input.h"
#include <iostream>

Input::Input()
{
}

Input::~Input()
{
}

Input& Input::Instance()
{
	static Input input;
	return input;
}

void Input::Update()
{
	MouseEvents();
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{

		case SDL_QUIT:
			m_quit = true;
			break;

		default:
			break;
		}
	}
}

const Uint8* Input::KeyboardEvents()
{
	const Uint8* keystates = SDL_GetKeyboardState(NULL);

	return keystates;


}

void Input::MouseEvents()
{
	int mouseX, mouseY;
	Uint32 buttons = SDL_GetMouseState(&mouseX, &mouseY);
	SDL_PumpEvents();  // make sure we have the latest mouse state.

	mouseX /= m_mouseScaleX;
	mouseY /= m_mouseScaleY;

	m_mousePos.x = mouseX;
	m_mousePos.y = mouseY;

	if (buttons == 1)
		m_leftMouseDown = true;
	else
		m_leftMouseDown = false;

	if (buttons == 4)
		m_rightMouseDown = true;
	else
		m_rightMouseDown = false;

	if (buttons == 5) 
	{
		m_leftMouseDown = true;
		m_rightMouseDown = true;
	}
}
