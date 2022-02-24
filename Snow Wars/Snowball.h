#pragma once
#include "Entity.h"
#include "Vec.h"

class Snowball : public Entity
{
public:
	Snowball() = default;
	Snowball(vec2 position, vec2 size, std::string spritePath) : Entity(position, size, spritePath) {}
	~Snowball() {}

	void Init(vec2 position, vec2 direction, int speed)
	{
		m_transform.GetPosition() = position;
		m_direction = direction;
		m_speed = speed;
	}
	bool OutsideBounds(int screenWidth, int screenHeight);

	virtual void Update() override;

private:
	vec2 m_direction = { 0,0 };

	int m_speed = 1;
};

