#include <string>
#include "PowerupController.h"
#include "Timer.h"

static const Timer& timer = Timer::Instance();
static const std::string fireUpPath = "Assets/FireRatePowerUp.png";

void PowerupController::Update()
{
	m_currentTime += timer.ElapsedSeconds();

	if (m_currentTime > m_spawnRate) 
	{
		m_currentTime = 0;
		Spawn();
	}

	for (int i = 0; i < m_spawnedPowerups.size(); i++)
	{
		m_spawnedPowerups[i].Update();
	}
}

void PowerupController::Spawn()
{
	Powerup powerup(CalculateSpawnPosition(),fireUpPath,1);
	m_spawnedPowerups.push_back(powerup);
}

vec2 PowerupController::CalculateSpawnPosition()
{
	vec2 spawnPosition = { 100,100 };

	spawnPosition.x = 100 + rand() % 1000;
	spawnPosition.y = 100 + rand() % 500;

	return spawnPosition;
}
