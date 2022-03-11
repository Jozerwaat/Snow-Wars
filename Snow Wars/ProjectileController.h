#pragma once
#include <vector>
#include "Projectile.h"
#include "Window.h"
#include "Player.h"

class ProjectileController
{
public:
	ProjectileController() = default;
	~ProjectileController() = default;
	
	void Init(Window& window, Player& player);
	static  ProjectileController& Instance();

	void Update();
	void SpawnProjectile(int projectileID, vec2 direction, vec2 snowmanPos, float rotationAngle = 0);

	std::vector<Projectile*> GetProjectiles() { return m_projectiles; }

	void PoolProjectile(int index);
	void PoolAll();
private:
	std::vector<Projectile*> m_projectiles = {};
	Window* m_window = nullptr;
	Player* m_player = nullptr;
};