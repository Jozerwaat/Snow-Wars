#pragma once
#include <vector>
#include "Powerup.h"
#include "Vec.h"
#include "Player.h"
#include "Window.h"

class PowerupController
{
public:
	PowerupController() = default;
	PowerupController(Window* window, Player* player) { m_player = player; m_window = window; }
	~PowerupController() = default;
	
	void Update();

	void Spawn();
	void Reset();
	void PoolAll();

private:
	vec2 CalculateSpawnPosition();
	Player* m_player = nullptr;
	Window* m_window = nullptr;
	Powerup m_fireRateUp;
	float m_currentTime = 0;
	float m_spawnRate = 8;

	std::vector<Powerup*> m_spawnedPowerups;
};