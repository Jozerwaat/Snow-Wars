#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Vec.h"
#include "Sprite.h"
#include "Window.h"

class Renderer
{
public:
	Renderer() = default;

	Renderer(const std::string& imagePath, int frameCount, vec2 size = NULL)
	{
		m_sprite = new Sprite(imagePath, size);
		m_frameCount = frameCount;
		m_size = vec2(m_sprite->GetSize().x / m_frameCount, m_sprite->GetSize().y);
	}
	~Renderer() = default;

	Sprite* GetSprite() { return m_sprite; }

	void Render(const vec2& position);
	void Render(const vec2& position, const float angle);

	void Animate(float speed, bool loopBack = false, bool loop = true);
	void Resize(vec2 newSize, vec2 newPosition = NULL);

	inline void SetFrame(int frame) { m_currentFrame = frame; }

	inline vec2 GetSize() { return m_size; }

private:
	Sprite* m_sprite = nullptr;

	vec2 m_size = { 0,0 };

	int m_frameCount = 1;
	int m_currentFrame = 0;

	float m_currentTime = 0;
	bool m_loopBack = false;
};

