#pragma once
#include "Transform.h"
#include "Renderer.h"
#include "Window.h"

class Button
{
public:
	Button() {}

	Button(vec2 position, std::string spritePath, int frameCount, vec2 size = NULL)
	{
		m_transform = Transform(position);
		m_renderer = Renderer(spritePath, frameCount, size);
	}
	~Button() {}

	void Hide() { m_hide = true; }

	void Show() { m_hide = false; }

	bool MouseOver();
	bool MouseDown();

	void MouseUp();
	void Update();
	void OnClick();
	void SetPosition(vec2 position) 
	{
		m_transform.GetPosition() = position;
	}
	void (*function)();

private:
	bool m_hide = false;
	bool m_mouseHeld = false;
	bool m_mouseEntered = false;
	Transform m_transform;
	Renderer m_renderer;
};

