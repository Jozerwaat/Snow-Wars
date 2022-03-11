#pragma once
#include "Entity.h"
#include "Vec.h"

class Snowball : public Entity
{
public:
	Snowball() = default;
	Snowball(vec2 position, std::string spritePath, int frameCount, vec2 size = NULL) : Entity(position, spritePath, frameCount, size) {}
	~Snowball() {}

	void Init(vec2 position, vec2 direction, float speed)
	{
		m_transform.GetPosition() = position;
		m_direction = direction;
		m_speed = speed;
	}
	bool OutsideBounds(int screenWidth, int screenHeight);

	virtual void Update() override;

private:
	vec2 m_direction = { 0,0 };

	float m_speed = 1.0f;
};

