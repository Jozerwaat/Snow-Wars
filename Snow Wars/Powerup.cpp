#include "Powerup.h"

void Powerup::Update()
{
	m_renderer.Render(m_transform.GetPosition());
	m_renderer.Animate(1.5f);
}
