#pragma once
#include <vector>
#include "Enemy.h"
#include "SnowballController.h"

class Player;

class EnemySpawner
{
public:
	EnemySpawner() = default;

	void InitSpawnedEnemy(Window& window, Player* player, SnowballController* snowballController);

	void Update();
	void Spawn(vec2 direction, vec2 snowmanPos);
	void CalculateSpawnPosition();
	void CheckCollision(int index);
	void PoolAll();

private:
	Window* m_screen = nullptr;

	std::vector<Enemy*> m_enemies = {};
	Player* m_player;
	float m_currentTime;
	SnowballController* m_snowballController;
};


