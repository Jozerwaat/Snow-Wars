#include "Renderer.h"
#include "Timer.h"

static const Timer& timer = Timer::Instance();

void Renderer::Render(const vec2& position)
{
	float frameWidth = m_sprite->GetSize().x / m_frameCount;

	SDL_Rect image;
	image.x = (int)((position.x - frameWidth) + (frameWidth / 2));
	image.y = (int)(position.y - (m_sprite->GetSize().y / 2));
	image.w = (int)frameWidth;
	image.h = (int)m_sprite->GetSize().y;

	SDL_Rect frame;
	frame.x = (int)(frameWidth * m_currentFrame);
	frame.y = 0;
	frame.w = (int)frameWidth;
	frame.h = (int)m_sprite->GetSize().y;
	SDL_RenderCopy(Window::m_renderer, m_sprite->GetTexture(), &frame, &image);
}

void Renderer::Render(const vec2& position, const float angle)
{
	float frameWidth = m_sprite->GetSize().x / m_frameCount;

	SDL_Rect image;
	image.x = (int)((position.x - frameWidth) + (frameWidth / 2));
	image.y = (int)(position.y - (m_sprite->GetSize().y / 2));
	image.w = (int)frameWidth;
	image.h = (int)m_sprite->GetSize().y;

	SDL_Rect frame;
	frame.x = (int)(frameWidth * m_currentFrame);
	frame.y = 0;
	frame.w = (int)frameWidth;
	frame.h = (int)m_sprite->GetSize().y;

	SDL_Point point;
	point.x = (int)(frameWidth - (frameWidth / 2));
	point.y = (int)(m_sprite->GetSize().y / 2);

	SDL_RenderCopyEx(Window::m_renderer, m_sprite->GetTexture(), &frame, &image, angle, &point, SDL_FLIP_NONE);
}

void Renderer::Animate(float speed, bool animateBack, bool loop)
{
	m_currentTime += (speed * timer.ElapsedSeconds());
	if (m_currentTime > 1)
	{
		m_currentTime = 0;

		if (m_loopBack == false)
			m_currentFrame += 1;

		if (m_loopBack)
			m_currentFrame -= 1;
	}

	if (loop && animateBack == false && m_currentFrame >= m_frameCount)
		m_currentFrame = 0;

	if (animateBack)
	{
		if (m_currentFrame >= m_frameCount -1)
			m_loopBack = true;
		if (m_currentFrame <= 0)
			m_loopBack = false;

	}
}

void Renderer::Resize(vec2 newSize, vec2 newPosition)
{
}
