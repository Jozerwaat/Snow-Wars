#include "ProjectileController.h"
#include "ObjectPool.h"

const ProjectileController& projectileController = ProjectileController::Instance();

static Projectile snowflake;
static int health = 0;
static ObjectPool<Projectile> objectPool;


void ProjectileController::Init(Window& window, Player& player)
{
	m_player = &player;
	m_window = &window;
	snowflake = Projectile(vec2(0, 0), "assets/SnowFlakeProjectile.png", 1);
	snowflake.SetSpeed(600);
	health = 3;
}

ProjectileController& ProjectileController::Instance()
{
	static ProjectileController p;
	return p;
}

void ProjectileController::Update()
{
	for (int i = 0; i < m_projectiles.size(); i++)
	{
		m_projectiles[i]->Update();

		if (m_projectiles[i]->OutsideBounds(m_window->GetWidth(), m_window->GetHeight()))
		{
			objectPool.Pool(m_projectiles[i]);
			m_projectiles.erase(m_projectiles.begin() + i);
			i--;
			continue;
		}
		if (m_projectiles[i]->GetCollider()->IsColliding(m_player->GetCollider())) 
		{
			if (m_player->IsInvincible())
				return;

			objectPool.Pool(m_projectiles[i]);
			m_projectiles.erase(m_projectiles.begin() + i);

			m_player->TakeDamage();
		}
	}
}

void ProjectileController::SpawnProjectile(vec2 direction, vec2 position, float rotationAngle)
{
	Projectile* projectile = objectPool.Get(snowflake);


	projectile->SetRadius(8);

	projectile->Init(position, direction, projectile->GetSpeed(), rotationAngle);
	m_projectiles.push_back(projectile);
}

void ProjectileController::PoolProjectile(int i)
{
	objectPool.Pool(m_projectiles[i]);
	m_projectiles.erase(m_projectiles.begin() + i);
}

void ProjectileController::PoolAll()
{
	for (int i = m_projectiles.size() - 1; i >= 0; i--)
	{
		objectPool.Pool(m_projectiles[i]);
		m_projectiles.pop_back();
	}
}