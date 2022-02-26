#include <SDL_image.h>
#include <iostream>
#include "Sprite.h"

Sprite::Sprite(const std::string& imagePath, vec2 size) :
	m_size(size)
{
	SDL_Surface* surface = IMG_Load(imagePath.c_str());

	if (size.x == 0 && size.y == 0) 
	{
		m_size.x = surface->w;
		m_size.y = surface->h;
	}

	if (surface == NULL)
		std::cout << "Failed to create surface for " + imagePath << std::endl;

	m_texture = SDL_CreateTextureFromSurface(Window::m_renderer, surface);

	if (m_texture == NULL)
		std::cout << "Failed to create texture for " + imagePath << std::endl;

	SDL_FreeSurface(surface);
}

Sprite::~Sprite()
{
	SDL_DestroyTexture(m_texture);
}