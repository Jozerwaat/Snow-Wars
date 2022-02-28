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
	inline bool LeftMouseDown() { return m_leftMouseDown; }
	inline bool RightMouseDown() { return m_rightMouseDown; }
	inline bool ResizeWindow() { return m_resize; }

private:
	void MouseEvents();

	vec2 m_mousePos = { 0,0 };
	float m_mouseScaleX = 1;
	float m_mouseScaleY = 1;

	bool m_quit = false;
	bool m_resize = false;
	bool m_leftMouseDown = false;
	bool m_rightMouseDown = false;
};

