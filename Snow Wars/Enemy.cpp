#include "Enemy.h"
#include "Timer.h"
#include "ProjectileController.h"

const static Timer& timer = Timer::Instance();
static double pi = 2 * acos(0.0);
static double piRadiant = pi / 180;
static float timeToExplode = 5;
void Enemy::Update()
{
	m_rotationAngle += (m_rotationSpeed * timer.ElapsedSeconds());
	m_renderer.Render(m_transform.GetPosition(), m_rotationAngle);
	m_transform.Translate((m_direction * m_speed) * timer.ElapsedSeconds());

	if (m_type == ENEMY_TYPE::SNOWMAN)
		m_renderer.Animate(30, true, false);
	
	if (m_type == ENEMY_TYPE::SNOWFLAKE) 
	{
		m_rotationTime += timer.ElapsedSeconds();
		timeToExplode = 13 + (-4.0f + (float(rand())) / float((RAND_MAX)) * 7.0f);
		//float randDirY = (-1.0f + (float(rand())) / float((RAND_MAX)) * 2.0f);
		if (m_rotationTime >= timeToExplode)
		{
			float angle = 0.0f;

			for (int i = 0; i < 6; i++)
			{
				vec2 directionOffset = { 0,0 };
				directionOffset.x = (float)cos((m_rotationAngle + angle) * piRadiant);
				directionOffset.y = (float)sin((m_rotationAngle + angle) * piRadiant);
				ProjectileController::Instance().SpawnProjectile(0, directionOffset, m_transform.GetPosition(), (m_rotationAngle + angle) + 90); //Add plus 90 to the angle to accomodate for the rotation offset
				angle += 60.0f;
			}
			m_destroy = true;
			m_rotationTime = 0;
		}
	}
	
	if (m_type == ENEMY_TYPE::SNOWMAN) 
	{
		vec2 lookDirection = { 0,0 };
		lookDirection = (m_player->GetTransform()->GetPosition() - m_transform.GetPosition()).normalized();
		m_rotationAngle = (float)((((atan2(-lookDirection.y, -lookDirection.x)) * 180) / pi) + 180) + 90; //Add plus 90 to the angle to accomodate for the rotation offset

		m_attackTime += timer.ElapsedSeconds();
		if (m_attackTime >= m_attackRate)
		{
			m_attackTime = 0;
			ProjectileController::Instance().SpawnProjectile(1,lookDirection, m_transform.GetPosition(), m_rotationAngle); //Add plus 90 to the angle to accomodate for the rotation offset
		}
	}
}

bool Enemy::OutsideBounds(int screenWidth, int screenHeight)
{
	if ((m_transform.GetPosition().x - 150) > screenWidth || (m_transform.GetPosition().x + 150) < 0)
		return true;
	if ((m_transform.GetPosition().y - 150) > screenHeight || (m_transform.GetPosition().y + 150) < 0)
		return true;

	return false;
}
