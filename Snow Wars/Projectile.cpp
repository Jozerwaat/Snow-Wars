#include "Projectile.h"
#include "Timer.h"

static const Timer& timer = Timer::Instance();

bool Projectile::OutsideBounds(int screenWidth, int screenHeight)
{
	if ((m_transform.GetPosition().x - 50) > screenWidth || (m_transform.GetPosition().x + 50) < 0)
		return true;
	if ((m_transform.GetPosition().y - 50) > screenHeight || (m_transform.GetPosition().y + 50) < 0)
		return true;

	return false;
}

void Projectile::Update()
{
	m_renderer.Render(m_transform.GetPosition(),m_rotationAngle);
	m_transform.Translate((m_direction * m_speed) * timer.ElapsedSeconds());
}