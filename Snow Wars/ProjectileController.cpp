#include "ProjectileController.h"
#include "ObjectPool.h"

const ProjectileController& projectileController = ProjectileController::Instance();

static Projectile snowflake;
static Projectile icicle;

static ObjectPool<Projectile> objectPool;


void ProjectileController::Init(Window& window, Player& player)
{
	m_player = &player;
	m_window = &window;
	snowflake = Projectile( vec2(0, 0), "assets/SnowFlakeProjectile.png", 1);
	snowflake.SetPrefab(PROJECTILE_TYPE::SNOWFLAKE, 600, 8);

	icicle = Projectile(vec2(0, 0), "assets/EnemySnowmanProjectile.png", 1);
	icicle.SetPrefab(PROJECTILE_TYPE::ICICLE, 500, 5);
}

ProjectileController& ProjectileController::Instance()
{
	static ProjectileController p;
	return p;
}

void ProjectileController::Update()
{
	for (unsigned int i = 0; i < m_projectiles.size(); i++)
	{
		m_projectiles[i]->Update();

		if (m_projectiles[i]->OutsideBounds(m_window->GetWidth(), m_window->GetHeight()))
		{
			objectPool.PoolProjectile(m_projectiles[i]);
			m_projectiles.erase(m_projectiles.begin() + i);
			i--;
			continue;
		}
		if (m_projectiles[i]->GetCollider()->IsColliding(m_player->GetCollider())) 
		{
			if (m_player->IsInvincible())
				return;

			objectPool.PoolProjectile(m_projectiles[i]);
			m_projectiles.erase(m_projectiles.begin() + i);

			m_player->TakeDamage();
		}
	}
}

void ProjectileController::SpawnProjectile(int projectileID, vec2 direction, vec2 position, float rotationAngle)
{
	Projectile* projectile = nullptr;
	if(projectileID == 0)
		projectile = objectPool.GetProjectile(snowflake);
	if (projectileID == 1)
		projectile = objectPool.GetProjectile(icicle);

	projectile->Init(position, direction, projectile->GetSpeed(), rotationAngle);
	m_projectiles.push_back(projectile);
}

void ProjectileController::PoolProjectile(int i)
{
	objectPool.PoolProjectile(m_projectiles[i]);
	m_projectiles.erase(m_projectiles.begin() + i);
}

void ProjectileController::PoolAll()
{
	for (int i = m_projectiles.size() - 1; i >= 0; i--)
	{
		objectPool.PoolProjectile(m_projectiles[i]);
		m_projectiles.pop_back();
	}
}