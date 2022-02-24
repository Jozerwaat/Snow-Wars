#pragma once
#include "Entity.h"

class Enemy : public Entity
{
public:
	Enemy() {}
	Enemy(vec2 position, vec2 size, std::string spritePath) : Entity(position, size, spritePath) {}
	~Enemy() {}

	void Init(vec2 position, vec2 direction, int speed)
	{
		m_transform.GetPosition() = position;
		m_direction = direction;
		m_speed = speed;
	}

	virtual void Update() override;
	bool OutsideBounds(int screenWidth, int screenHeight);


private:
	bool m_instantiated = false;
	vec2 m_direction;
	int m_speed = 1;
};

