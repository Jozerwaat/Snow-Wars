#pragma once
#include <vector>
#include "Enemy.h"
#include "SnowballController.h"

class Player;

class EnemySpawner
{
public:
	EnemySpawner() = default;

	void Init(Window& window, Player* player, SnowballController* snowballController);

	void Update();
	void Spawn(vec2 direction, vec2 snowmanPos);
	void CalculateSpawnPosition();
	void CheckCollision(int index);
	void PoolAll();

private:
	Window* m_screen = nullptr;

	std::vector<Enemy*> m_enemies = {};
	Player* m_player = nullptr;
	float m_currentTime = 0;
	SnowballController* m_snowballController = nullptr;
};


