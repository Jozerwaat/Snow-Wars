#pragma once
#include <vector>
#include <list>
#include <iostream>
#include <map>
#include "Enemy.h"
#include "Projectile.h"

template <typename T>
class ObjectPool
{
public:
	ObjectPool() : m_objects() {}

	/// Mark the given object for reuse in the future.
	void Pool(T* obj) { m_objects.emplace_back(obj); }

	T* Get() {
		if (m_objects.empty()) // no objects are free
			return new T();

		auto obj = m_objects.back();	// get the last object in the list
		m_objects.pop_back();

		return obj;
	}

	T* Get(T object) {
		if (m_objects.empty()) // no objects are free
			return new T(object);

		auto obj = m_objects.back();	// get the last object in the list
		m_objects.pop_back();

		return obj;
	}


	void MapPool(Enemy* enemy)
	{
		m_enemyObjects[*enemy].emplace_back(enemy);
	}

	Enemy* GetEnemy(Enemy enemy) 
	{
		if (m_enemyObjects[enemy].empty()) 
		{
			return new Enemy(enemy);
		} // no objects are free

		auto obj = m_enemyObjects[enemy].back();	// get the last object in the list
		m_enemyObjects[enemy].pop_back();
		return obj;
	}

	void PoolProjectile(Projectile* projectile)
	{
		m_projectiles[*projectile].emplace_back(projectile);
	}

	Projectile* GetProjectile(Projectile projectile)
	{
		if (m_projectiles[projectile].empty())
		{
			return new Projectile(projectile);
		} // no objects are free

		auto obj = m_projectiles[projectile].back();	// get the last object in the list
		m_projectiles[projectile].pop_back();
		return obj;
	}


private:
	std::vector<T*> m_objects;
	std::map<Enemy, std::vector<Enemy*>> m_enemyObjects = {};
	std::map<Projectile, std::vector<Projectile*>> m_projectiles = {};
};