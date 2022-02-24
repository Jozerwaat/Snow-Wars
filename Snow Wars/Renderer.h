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

	Renderer(vec2 size, const std::string& imagePath) 
	{ 
		m_sprite = new Sprite(size, imagePath);
	}


	Sprite* GetSprite()
	{
		return m_sprite;
	}

	void Render(const vec2& position);
	void Render(const vec2& position, const float angle);

	void Animate(int speed);


private:
	Sprite* m_sprite = nullptr;
};

