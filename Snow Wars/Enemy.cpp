#include "Enemy.h"
#include "Timer.h"

const static Timer& timer = Timer::Instance();
static double pi = 2 * acos(0.0);
static double piRadiant = pi / 180;
static float timeToExplode = 5;
static float currentTime = 0;
void Enemy::Update()
{
	m_rotationAngle += (m_rotationSpeed * timer.ElapsedSeconds());
	m_renderer.Render(m_transform.GetPosition(), m_rotationAngle);
	m_transform.Translate((m_direction * m_speed) * timer.ElapsedSeconds());
	
	/*
	if (m_type == ENEMY_TYPE::SNOWFLAKE) 
	{
		currentTime += timer.ElapsedSeconds();
		if (currentTime >= timeToExplode) 
		{
			float angle = 0.0f;
	
			for (int i = 0; i < 6; i++)
			{
				Enemy* projectile = new Enemy(m_transform.GetPosition(), "assets/SnowflakeProjectile.png", 1);
				vec2 directionOffset = { 0,0 };
				directionOffset.x = cos(angle) * piRadiant;
				directionOffset.y = sin(angle) * piRadiant;
				angle += 60.0f;
				projectile->InitSpawnedEnemy(m_transform.GetPosition(), directionOffset, 100, 1);
				//m_snowballController->SpawnSnowball(directionOffset, m_transform->GetPosition());
			}
		}
	}
	*/
}

bool Enemy::OutsideBounds(int screenWidth, int screenHeight)
{
	if ((m_transform.GetPosition().x - 150) > screenWidth || (m_transform.GetPosition().x + 150) < 0)
		return true;
	if ((m_transform.GetPosition().y - 150) > screenHeight || (m_transform.GetPosition().y + 150) < 0)
		return true;

	return false;
}
