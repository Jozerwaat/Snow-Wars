#include <SDL_image.h>
#include <iostream>
#include "Sprite.h"

Sprite::Sprite(vec2 size, const std::string& imagePath) :
	m_size(size)
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