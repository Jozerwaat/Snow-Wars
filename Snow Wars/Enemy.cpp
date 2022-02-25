#include "Enemy.h"
#include "Timer.h"

const static Timer& timer = Timer::Instance();

void Enemy::Update()
{
	m_renderer.Animate(30);
	m_renderer.Render(m_transform.GetPosition());
	m_transform.Translate((m_direction * m_speed) * timer.ElapsedSeconds());
}

bool Enemy::OutsideBounds(int screenWidth, int screenHeight)
{
	if ((m_transform.GetPosition().x - 150) > screenWidth || (m_transform.GetPosition().x + 150) < 0)
		return true;
	if ((m_transform.GetPosition().y - 150) > screenHeight || (m_transform.GetPosition().y + 150) < 0)
		return true;

	return false;
}
