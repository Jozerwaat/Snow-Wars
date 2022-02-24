#pragma once
#include <SDL.h>
#include "Vec.h"

class Input
{
public:
	Input();
	~Input();

	void Update();
	
	inline SDL_Keycode& GetKey() { return m_pressedKey;}

	inline vec2 GetMousePos()const { return m_mousePos; }

	inline bool QuitGame() const { return m_quit; }

private:
	vec2 m_mousePos = { 0,0 };
	SDL_Keycode m_pressedKey = 0;
	bool m_quit = false;
};

