#include "Renderer.h"
#include "Timer.h"

static const Timer& timer = Timer::Instance();

void Renderer::Render(const vec2& position)
{
	float frameWidth = m_sprite->GetSize().x / m_frameCount;

	SDL_Rect image;
	image.x = (position.x - frameWidth) + (frameWidth / 2);
	image.y = position.y - (m_sprite->GetSize().y / 2);
	image.w = frameWidth;
	image.h = m_sprite->GetSize().y;

	SDL_Rect frame;
	frame.x = frameWidth * m_currentFrame;
	frame.y = 0;
	frame.w = frameWidth;
	frame.h = m_sprite->GetSize().y;
	SDL_RenderCopy(Window::m_renderer, m_sprite->GetTexture(), &frame, &image);
}

void Renderer::Render(const vec2& position, const float angle)
{
	SDL_Rect rect = { position.x - (m_sprite->GetSize().x / 2), position.y - (m_sprite->GetSize().y / 2), m_sprite->GetSize().x, m_sprite->GetSize().y };
	SDL_Point point;
	point.x = (m_sprite->GetSize().x / 2);
	point.y = (m_sprite->GetSize().y / 2);

	SDL_RenderCopyEx(Window::m_renderer, m_sprite->GetTexture(), nullptr, &rect, angle, &point, SDL_FLIP_NONE);
}

void Renderer::Animate(float speed)
{
	m_currentTime += (speed * timer.ElapsedSeconds());
	if (m_currentTime > 1)
	{
		m_currentTime = 0;
		m_currentFrame += 1;
	}

	if (m_currentFrame >= m_frameCount)
		m_currentFrame = 0;
}
