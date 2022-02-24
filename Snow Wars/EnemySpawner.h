#pragma once
#include <vector>
#include "Enemy.h"
#include "SnowballController.h"

class Player;

class EnemySpawner
{
public:
	EnemySpawner() = default;

	void Init(Window& window, Player* player, SnowballController* snowballController)
	{
		m_screen = &window;
		m_player = player;
		m_snowballController = snowballController;
	}

	void Update();
	void Spawn(vec2 direction, vec2 snowmanPos);
	void CalculateSpawnPosition();
	void CheckCollision(int index);
	void PoolAll();

private:
	Window* m_screen = nullptr;

	std::vector<Enemy*> m_enemies;
	Player* m_player;
	float m_currentTime;
	SnowballController* m_snowballController;
};


