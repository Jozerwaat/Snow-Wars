#include "EnemySpawner.h"
#include "ObjectPool.h"
#include "Timer.h"
#include "Player.h"
#include "ScoreController.h"

static const Timer& timer = Timer::Instance();
static const ScoreController& scoreController = ScoreController::Instance();

static char spritePath[] = "assets/IceBall.png";

static ObjectPool<Enemy> pool;
static const int speed = 500;
static  int spawnSpeed = 4; //Enemies spawned per second
static float spawnSpeedTimeIncrease = 30;

void EnemySpawner::Update()
{
	if (timer.TotalTimeSeconds() > spawnSpeedTimeIncrease) 
	{
		spawnSpeedTimeIncrease *= 2;
		spawnSpeed += 1;
	}

	m_currentTime += timer.ElapsedSeconds();
	
	if ((m_currentTime * spawnSpeed) > 1)
	{
		m_currentTime = 0;
		CalculateSpawnPosition();
	}
	for (int i = 0; i < m_enemies.size(); i++)
	{
		if (m_enemies[i]->OutsideBounds(m_screen->GetWidth(), m_screen->GetHeight()))
		{
			pool.Pool(m_enemies[i]);
			m_enemies.erase(m_enemies.begin() + i);
			i--;
			continue;
		}

		CheckCollision(i);

		if (m_enemies[i]->GetHealth() <= 0)
		{
			scoreController.Instance().AddScore(10);
			pool.Pool(m_enemies[i]);
			m_enemies.erase(m_enemies.begin() + i);
			i--;
			continue;
		}


		m_enemies[i]->Update();

	}
}

void EnemySpawner::CheckCollision(int index)
{
	for (int j = 0; j < m_snowballController->GetSnowballs().size(); j++)
	{
		if (m_enemies[index]->GetCollider()->IsColliding(m_snowballController->GetSnowballs()[j]->GetCollider()))
		{
			m_snowballController->PoolSnowball(j);
			m_enemies[index]->TakeDamage();

		}
	}

	if (m_enemies[index]->GetCollider()->IsColliding(m_player->GetCollider()))
	{
		m_enemies[index]->TakeDamage();
		m_enemies[index]->TakeDamage();
		m_enemies[index]->TakeDamage();

		m_player->TakeDamage();

	}
}

void EnemySpawner::PoolAll()
{
	for (int i = m_enemies.size() - 1; i >= 0; i--)
	{
		pool.Pool(m_enemies[i]);
		m_enemies.pop_back();
	}
	m_currentTime = 0;
	spawnSpeed = 4;
	spawnSpeedTimeIncrease = 30;
}

void EnemySpawner::Spawn(vec2 direction, vec2 position)
{
	Enemy* enemy = pool.Get();
	m_enemies.push_back(enemy);

	if (enemy->IsInstantiated() == false)
		*enemy = Enemy(position, spritePath, 24);

	enemy->SetRadius(25);
	int enemySpeed = speed + (-140 + (rand() % 260));
	enemy->Init(position, direction, enemySpeed);
	enemy->SetHealth(3);	
}

void EnemySpawner::CalculateSpawnPosition()
{
	int spawnSide = rand() % 4; //0 = left side, 1 = top side, 2 is right side, 3 is bottom side
	int homingChance = rand() % 100;
	bool isHoming = false;

	if (homingChance > 70)
		isHoming = true;

	vec2 randomPos = vec2(1000, 0);
	vec2 randomDir = vec2(0, 0);

	switch (spawnSide)
	{
	case 0://Spawns on left side
	{
		int randY = rand() % m_screen->GetHeight();
		float randDirY = (-1.0f + (float(rand())) / float((RAND_MAX)) * 2.0f);
		randomPos = vec2(0, randY);
		randomDir = vec2(1, randDirY);
		break;
	}

	case 1://Spawns on top side
	{
		int randX = rand() % m_screen->GetWidth();
		float randDirX = (-1.0f + (float(rand())) / float((RAND_MAX)) * 2.0f);
		randomPos = vec2(randX, 0);
		randomDir = vec2(randDirX, 1);
		break;
	}

	case 2://Spawns on right side
	{
		int randY = rand() % m_screen->GetHeight();
		float randDirY = (-1.0f + (float(rand())) / float((RAND_MAX)) * 2.0f);
		randomPos = vec2(m_screen->GetWidth(), randY);
		randomDir = vec2(-1, randDirY);
		break;
	}

	case 3://Spawns on top side
	{
		int randX = rand() % m_screen->GetWidth();
		float randDirX = (-1.0f + (float(rand())) / float((RAND_MAX)) * 2.0f);
		randomPos = vec2(randX, m_screen->GetHeight());
		randomDir = vec2(randDirX, -1);
		break;
	}
	}

	if (isHoming)
		randomDir = (m_player->GetTransform().GetPosition() - randomPos).normalized();

	Spawn(randomDir, randomPos);
}

