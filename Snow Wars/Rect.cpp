#include <SDL_image.h>
#include <iostream>
#include "Rect.h"

Rect::Rect(vec2 size, vec2 pos, int r, int g, int b, int a) :
	m_size(size), m_pos(pos), m_r(r), m_g(g), m_b(b), m_a(a)
{
}

Rect::Rect(vec2 size, vec2 pos, const std::string& imagePath) :
	m_size(size), m_pos(pos)
{
	SDL_Surface* surface = IMG_Load(imagePath.c_str());

	if (surface == NULL)
		std::cout << "Failed to create surface" << std::endl;

	m_texture = SDL_CreateTextureFromSurface(Window::m_renderer, surface);

	if (m_texture == NULL)
		std::cout << "Failed to create texture" << std::endl;

	SDL_FreeSurface(surface);
}

Rect::~Rect()
{
	SDL_DestroyTexture(m_texture);
}

void Rect::Draw() const
{
	SDL_Rect rect = { m_pos.x, m_pos.y, m_size.x, m_size.y };

	if (m_texture)
	{
		SDL_RenderCopy(Window::m_renderer, m_texture, nullptr, &rect);
	}
	else
	{
		SDL_SetRenderDrawColor(Window::m_renderer, m_r, m_g, m_b, m_a);
		SDL_RenderFillRect(Window::m_renderer, &rect);
	}
}
