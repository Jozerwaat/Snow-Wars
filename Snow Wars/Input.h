#pragma once
#include <SDL.h>
#include "Vec.h"

class Input
{
public:
	Input();
	~Input();

	static Input& Instance();

	void Update();
	
	vec2& GetMousePos() { return m_mousePos; }
	const Uint8* KeyboardEvents();

	inline bool QuitGame() const { return m_quit; }
	inline bool MouseDown() { return m_mouseDown; }
	inline bool ResizeWindow() {return m_resize;}

private:
	void MouseEvents();

	vec2 m_mousePos = { 0,0 };
	float m_mouseScaleX =1;
	float m_mouseScaleY = 1;
	
	bool m_quit = false;
	bool m_resize = false;
	bool m_mouseDown;
};

