#pragma once
#include "Entity.h"

class Enemy : public Entity
{
public:
	Enemy() {}
	Enemy(vec2 position, std::string spritePath, int frameCount, vec2 size = NULL) : Entity(position, spritePath, frameCount, size) {}
	~Enemy() {}

	void Init(vec2 position, vec2 direction, int speed)
	{
		m_transform.GetPosition() = position;
		m_direction = direction;
		m_speed = speed;
	}

	virtual void Update() override;
	bool OutsideBounds(int screenWidth, int screenHeight);
	inline void SetHealth(int health) { m_health = health; }
	inline int& GetHealth() { return m_health; }

	inline void TakeDamage() { m_health--; }

private:
	bool m_instantiated = false;
	vec2 m_direction;
	int m_speed = 1;
	int m_health;
};

