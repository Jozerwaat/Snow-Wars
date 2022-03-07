#pragma once
#include "Entity.h"

enum class ENEMY_TYPE
{
	ICE_BALL = 0,
	SNOWFLAKE = 1
};


class Enemy : public Entity
{
public:
	Enemy() {}
	Enemy(const Enemy& copy) : Entity(copy)
	{
		*this = copy;
		m_collider = CircleCollider(25, &m_transform);
	}
	Enemy(vec2 position, std::string spritePath, int frameCount, vec2 size = NULL) : Entity(position, spritePath, frameCount, size) {}
	~Enemy() {}

	void Init(vec2 position, vec2 direction, int speed, int health)
	{
		m_transform.GetPosition() = position;
		m_direction = direction;
		m_speed = speed;
		m_health = health;
	}

	virtual void Update() override;
	bool OutsideBounds(int screenWidth, int screenHeight);
	inline void SetHealth(int health) { m_health = health; }
	inline int& GetHealth() { return m_health; }

	inline void TakeDamage() { m_health--; }

	void SetRotationSpeed(float speed) { m_rotationSpeed = speed; }

	ENEMY_TYPE GetEnemyType() { return m_type; }
	void SetType(ENEMY_TYPE type) { m_type = type; }

	bool operator<(const Enemy& other) const {
		return m_type < other.m_type;
	}

private:
	ENEMY_TYPE m_type = ENEMY_TYPE::ICE_BALL;
	vec2 m_direction = { 0,0 };
	int m_speed = 1;
	int m_rotationSpeed = 0;
	int m_health = 3;
	float m_rotationAngle = 0;
};

