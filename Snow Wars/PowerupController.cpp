#include <string>
#include "PowerupController.h"
#include "Timer.h"
#include "ObjectPool.h"

static const Timer& timer = Timer::Instance();
static const std::string fireUpPath = "Assets/FireRatePowerUp.png";

static ObjectPool<Powerup> pool;
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
		m_spawnedPowerups[i]->Update();
		if (m_spawnedPowerups[i]->GetCollider()->IsColliding(m_player->GetCollider()))
		{
			pool.Pool(m_spawnedPowerups[i]);
			m_spawnedPowerups.erase(m_spawnedPowerups.begin() + i);
			i--;
			
			m_player->StartPowerUp(POWERUP_TYPE::FIRE_RATE);
		}
	}
}

void PowerupController::Spawn()
{
	Powerup* powerup = pool.Get();
	if (powerup->IsInstantiated() == false)
		*powerup = Powerup(CalculateSpawnPosition(), fireUpPath, 2);

	powerup->SetRadius(50);
	powerup->GetTransform()->GetPosition() = CalculateSpawnPosition();
	m_spawnedPowerups.push_back(powerup);
	m_spawnRate = 14 + (-5 + (rand() % 10));
}

vec2 PowerupController::CalculateSpawnPosition()
{
	vec2 spawnPosition = { 100,100 };

	spawnPosition.x = 200 + (rand() % (m_window->GetWidth() - 400));
	spawnPosition.y = 200 + (rand() % (m_window->GetHeight() - 400));

	return spawnPosition;
}

void PowerupController::Reset()
{
	m_currentTime = 0;
	m_spawnRate = 14 + (-5 + (rand() % 10));
	PoolAll();
}

void PowerupController::PoolAll()
{
	for (int i = m_spawnedPowerups.size() - 1; i >= 0; i--)
	{
		pool.Pool(m_spawnedPowerups[i]);
		m_spawnedPowerups.pop_back();
	}
}