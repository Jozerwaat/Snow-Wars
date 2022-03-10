#include "EnemySpawner.h"
#include "ObjectPool.h"
#include "Timer.h"
#include "Player.h"
#include "ScoreController.h"

static const Timer& timer = Timer::Instance();
static const ScoreController& scoreController = ScoreController::Instance();

static Enemy iceBall;
static Enemy snowflake;
static Enemy snowman;
static ObjectPool<Enemy> pool;

static float spawnSpeed = 2.0f; //Enemies spawned per second
static float spawnSpeedTimeIncrease = 30;

void EnemySpawner::Init(Window& window, Player* player, SnowballController* snowballController)
{
	m_screen = &window;
	m_player = player;
	m_snowballController = snowballController;

	iceBall = Enemy(vec2(0, 0), "assets/IceBall.png", 1);
	iceBall.SetPrefab(ENEMY_TYPE::ICE_BALL, 25, 500, 500, m_player);

	snowflake = Enemy(vec2(0, 0), "assets/Snowflake.png", 1);
	snowflake.SetPrefab(ENEMY_TYPE::SNOWFLAKE, 35, 80, 90, m_player);

	snowman = Enemy(vec2(0, 0), "assets/EnemySnowman.png", 12);
	snowman.SetPrefab(ENEMY_TYPE::SNOWMAN, 25, 60, 0, m_player);
}

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
		if (m_enemies[i]->DestroyEnemy()) 
		{
			pool.MapPool(m_enemies[i]);
			m_enemies.erase(m_enemies.begin() + i);
			i--;
			continue;
		}
		if (m_enemies[i]->OutsideBounds(m_screen->GetWidth(), m_screen->GetHeight()))
		{
			pool.MapPool(m_enemies[i]);
			m_enemies.erase(m_enemies.begin() + i);
			i--;
			continue;
		}

	CheckCollision(i);

		if (m_enemies[i]->GetHealth() <= 0)
		{
			scoreController.Instance().AddScore(10);
			pool.MapPool(m_enemies[i]);
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
		if (m_player->IsInvincible())
			return;

		pool.MapPool(m_enemies[index]);
		m_enemies.erase(m_enemies.begin() + index);

		m_player->TakeDamage();
	}
}

void EnemySpawner::PoolAll()
{
	for (int i = m_enemies.size() - 1; i >= 0; i--)
	{
		pool.MapPool(m_enemies[i]);
		//pool.Pool(m_enemies[i]);
		m_enemies.pop_back();
	}
	m_currentTime = 0;
	spawnSpeed = 2.0f;
	spawnSpeedTimeIncrease = 30;
}

void EnemySpawner::Spawn(vec2 direction, vec2 position)
{
	Enemy* enemy = nullptr;

	int randomEnemy = 0;
	int enemyChance = rand() % 100;
	
	if (enemyChance >= 0 && enemyChance < 60)
		randomEnemy = 0;
	else if (enemyChance >= 60 && enemyChance < 85)
		randomEnemy = 1;
	else if (enemyChance >= 85)
		randomEnemy = 2;

	if (randomEnemy == 0) 
		enemy = pool.GetEnemy(iceBall);
	else if (randomEnemy == 1) 
		enemy = pool.GetEnemy(snowflake);
	else if (randomEnemy == 2)
		enemy = pool.GetEnemy(snowman);

	int enemySpeed = enemy->GetBaseSpeed() + (-(enemy->GetBaseSpeed() * 0.3f) + (rand() % enemy->GetBaseSpeed() * 0.3f));
	enemy->Init(position, direction, enemySpeed,3, false);

	m_enemies.push_back(enemy);
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
		randomPos = vec2(-25, randY);
		randomDir = vec2(1, randDirY);
		break;
	}

	case 1://Spawns on top side
	{
		int randX = rand() % m_screen->GetWidth();
		float randDirX = (-1.0f + (float(rand())) / float((RAND_MAX)) * 2.0f);
		randomPos = vec2(randX, -25);
		randomDir = vec2(randDirX, 1);
		break;
	}

	case 2://Spawns on right side
	{
		int randY = rand() % m_screen->GetHeight();
		float randDirY = (-1.0f + (float(rand())) / float((RAND_MAX)) * 2.0f);
		randomPos = vec2(m_screen->GetWidth() + 25, randY);
		randomDir = vec2(-1, randDirY);
		break;
	}

	case 3://Spawns on top side
	{
		int randX = rand() % m_screen->GetWidth();
		float randDirX = (-1.0f + (float(rand())) / float((RAND_MAX)) * 2.0f);
		randomPos = vec2(randX, m_screen->GetHeight() + 25);
		randomDir = vec2(randDirX, -1);
		break;
	}
	}

	if (isHoming)
		randomDir = (m_player->GetTransform()->GetPosition() - randomPos).normalized();

	Spawn(randomDir, randomPos);
}

