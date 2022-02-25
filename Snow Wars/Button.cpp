#include "Button.h"
#include <iostream>
#include "Input.h"

const static Input& playerInput = Input::Instance();

bool Button::MouseOver()
{
	vec2 mousePos = playerInput.Instance().GetMousePos();
	vec2 spriteSize = m_renderer.GetSize();
	vec2 position = m_transform.GetPosition();
	float widthOffset = spriteSize.x / 2;
	float heightOffset = spriteSize.y /2;

	if (mousePos.x > (position.x - widthOffset) && mousePos.x < (position.x + widthOffset))
	{
		if (mousePos.y > (position.y - heightOffset) && mousePos.y < (position.y + heightOffset))
			return true;
	}

	return false;
}

bool Button::MouseDown()
{
	m_renderer.SetFrame(1);
	return false;
}

void Button::MouseUp()
{
}


void Button::Update()
{
	if (m_hide)
		return;

	if (MouseOver())
	{
		if (playerInput.Instance().MouseDown())
		{
			m_mouseHeld = true;
			m_renderer.SetFrame(1);
		}
		if (playerInput.Instance().MouseDown() == false && m_mouseHeld)
		{
			m_mouseHeld = false;
			OnClick();
		}

	}
	else if (MouseOver() == false || playerInput.Instance().MouseDown() == false)
	{
		m_mouseHeld = false;
		m_renderer.SetFrame(0);
	}

	m_renderer.Render(m_transform.GetPosition());

}

void Button::OnClick()
{
	m_renderer.SetFrame(0);
	function();
}
