#pragma once
#include <vector>
#include "Powerup.h"
#include "Vec.h"

class PowerupController
{
public:
	PowerupController() {}
	~PowerupController() = default;
	void Update();

	void Spawn();
private:
	vec2 CalculateSpawnPosition();

	Powerup m_fireRateUp;
	float m_currentTime = 0;
	float m_spawnRate = 10;

	std::vector<Powerup> m_spawnedPowerups;
};