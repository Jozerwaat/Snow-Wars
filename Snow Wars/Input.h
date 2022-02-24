#pragma once
#include <SDL.h>
#include "Vec.h"

class Input
{
public:
	Input();
	~Input();

	void Update();
	
	vec2 GetMousePos() { return m_mousePos;}

	SDL_Keycode& GetKey();
	inline bool QuitGame() { return m_quit;}

private:
	vec2 m_mousePos;
	SDL_Keycode m_pressedKey = 0;
	bool m_quit = false;
};

