#include "Renderer.h"

void Renderer::Render(const vec2& position)
{
	SDL_Rect rect = { position.x - (m_sprite->GetSize().x / 2), position.y - (m_sprite->GetSize().y/ 2), m_sprite->GetSize().x, m_sprite->GetSize().y };

	SDL_RenderCopy(Window::m_renderer, m_sprite->GetTexture(), nullptr, &rect);
}

void Renderer::Render(const vec2& position, const float angle)
{
	SDL_Rect rect = { position.x - (m_sprite->GetSize().x / 2), position.y - (m_sprite->GetSize().y / 2), m_sprite->GetSize().x, m_sprite->GetSize().y };
	SDL_Point point;
	point.x = (m_sprite->GetSize().x / 2);
	point.y = (m_sprite->GetSize().y / 2);

	SDL_RenderCopyEx(Window::m_renderer, m_sprite->GetTexture(), nullptr, &rect, angle, &point, SDL_FLIP_NONE);
}