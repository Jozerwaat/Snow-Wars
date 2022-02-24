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

void Sprite::Draw() const
{
	vec2 drawPos;
	drawPos.x = (m_pos.x - (m_size.x / 2));
	drawPos.y = (m_pos.x - (m_size.y / 2));
	SDL_Rect rect = { drawPos.x, drawPos.y, m_size.x, m_size.y };

	SDL_RenderCopy(Window::m_renderer, m_texture, nullptr, &rect);
}
