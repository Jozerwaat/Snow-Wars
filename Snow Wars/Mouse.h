#pragma once
#include <SDL.h>
#include "Transform.h"
#include "Renderer.h"
#include "Input.h"

const static Input& playerInput = Input::Instance();

class Mouse
{
public:
	Mouse() = default;

	Mouse(vec2 position, std::string spritePath, int frameCount, vec2 size = NULL)
	{
		m_transform = Transform(position);
		m_renderer = Renderer( spritePath, frameCount, size);
		SDL_ShowCursor(false);
	}

	void Update()
	{
		m_renderer.Render(playerInput.Instance().GetMousePos());
	}
private:
	Transform m_transform;
	Renderer m_renderer;
};