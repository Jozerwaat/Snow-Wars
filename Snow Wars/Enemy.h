#pragma once
#include "Entity.h"
#include "Player.h"

enum class ENEMY_TYPE
{
	ICE_BALL = 0,
	SNOWFLAKE = 1,
	SNOWMAN = 2
};


class Enemy : public Entity
{
public:
	Enemy() {}
	Enemy(const Enemy& copy) : Entity(copy)
	{
		*this = copy;
		m_collider = CircleCollider(m_colliderRadius, &m_transform);
	}
	Enemy(vec2 position, std::string spritePath, int frameCount, vec2 size = NULL) : Entity(position, spritePath, frameCount, size) {}
	~Enemy() {}

	void Init(vec2 position, vec2 direction, float speed, int health, bool destroy = false)
	{
		m_destroy = destroy;
		m_transform.GetPosition() = position;
		m_direction = direction;
		m_speed = speed;
		m_health = health;
	}

	void SetPrefab(ENEMY_TYPE type, float colliderRadius, float baseSpeed, float rotationSpeed, Player* player)
	{
		m_type = type;
		m_colliderRadius = colliderRadius;
		m_baseSpeed = baseSpeed;
		m_rotationSpeed = rotationSpeed;
		m_player = player;
	}

	bool DestroyEnemy() { return m_destroy; }
	virtual void Update() override;
	bool OutsideBounds(int screenWidth, int screenHeight);
	inline void SetHealth(int health) { m_health = health; }
	inline int& GetHealth() { return m_health; }

	inline void TakeDamage() { m_health--; }

	float GetBaseSpeed() { return m_baseSpeed; }

	ENEMY_TYPE GetEnemyType() { return m_type; }

	bool operator<(const Enemy& other) const {
		return m_type < other.m_type;
	}

private:
	Player* m_player = nullptr;
	bool m_destroy = false;
	ENEMY_TYPE m_type = ENEMY_TYPE::ICE_BALL;
	vec2 m_direction = { 0,0 };
	int m_health = 3;
	float m_speed = 1.0f;
	float m_baseSpeed = 1.0f;
	float m_rotationSpeed = 0;
	float m_colliderRadius = 10.0f;
	float m_rotationAngle = 0;
	float m_rotationTime = 0;

	float m_attackTime = 0;
	float m_attackRate = 3.0f;
};

