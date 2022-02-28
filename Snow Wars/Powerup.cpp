#include "Powerup.h"

void Powerup::Update()
{
	m_renderer.Render(m_transform.GetPosition());
}
