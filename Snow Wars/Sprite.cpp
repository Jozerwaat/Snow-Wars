#include <SDL_image.h>
#include <iostream>
#include "Sprite.h"

Sprite::Sprite(vec2 size, vec2 pos, const std::string& imagePath) :
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

Sprite::~Sprite()
{
	SDL_DestroyTexture(m_texture);
}

void Sprite::Draw(vec2 pos)
{
	m_pos = pos;
	SDL_Rect rect = { m_pos.x - (m_size.x / 2), m_pos.y - (m_size.y / 2), m_size.x, m_size.y };

	SDL_RenderCopy(Window::m_renderer, m_texture, nullptr, &rect);
}
