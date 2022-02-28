#pragma once
#include <vector>
#include "Powerup.h"
#include "Vec.h"
#include "Player.h"

class PowerupController
{
public:
	PowerupController() = default;
	PowerupController(Player* player) { m_player = player; }
	~PowerupController() = default;
	
	void Update();

	void Spawn();

private:
	vec2 CalculateSpawnPosition();
	Player* m_player = nullptr;
	Powerup m_fireRateUp;
	float m_currentTime = 0;
	float m_spawnRate = 10;

	std::vector<Powerup> m_spawnedPowerups;
};