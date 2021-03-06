#pragma once
#include "Entity.h"
#include "Vec.h"

enum class PROJECTILE_TYPE
{
	SNOWFLAKE = 0,
	ICICLE = 1
};

class Projectile : public Entity
{
public:
	Projectile() = default;
	Projectile(const Projectile& copy) : Entity(copy)
	{
		*this = copy;
		m_collider = CircleCollider(m_colliderRadius, &m_transform);
	}
	Projectile(vec2 position, std::string spritePath, int frameCount, vec2 size = NULL) : Entity(position, spritePath, frameCount, size) {}
	~Projectile() {}

	void SetPrefab(PROJECTILE_TYPE type, float speed, float colliderRaidus) 
	{
		m_type = type;
		m_speed = speed;
		m_colliderRadius = colliderRaidus;
	}

	void Init(vec2 position, vec2 direction, float speed, float rotationAngle = 0)
	{
		m_transform.GetPosition() = position;
		m_direction = direction;
		m_speed = speed;
		m_rotationAngle = rotationAngle;
	}

	void SetSpeed(float speed) { m_speed = speed; }
	float GetSpeed() { return m_speed; }
	bool OutsideBounds(int screenWidth, int screenHeight);

	virtual void Update() override;

	bool operator<(const Projectile& other) const {
		return m_type < other.m_type;
	}


private:
	PROJECTILE_TYPE m_type = PROJECTILE_TYPE::SNOWFLAKE;
	vec2 m_direction = { 0,0 };

	float m_rotationAngle = 0;
	float m_colliderRadius = 5;
	float m_speed = 1.0f;
};

/*When an enemy spawns it has the ability to shoot a projectiles
A projectile controller is responsible for updating the projectile, spawning it and destroy it (pooling)
The creation of projectiles prefabs should happen in the projectile controller or enemy




*/