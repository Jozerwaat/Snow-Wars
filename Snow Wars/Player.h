#pragma once
#include "Entity.h"

class SnowballController;
class Transform;

class Player : public Entity
{
public:
	Player() = default;

	Player(vec2 position, vec2 size, std::string spritePath) : Entity(position, size, spritePath) {}

	void Update() override;

	Transform GetTransform() const { return m_transform; }

	void Init(SnowballController& snowballController);

private:
	void CalculateAimAngle();
	void Move();
	void Shoot();
	void Aim();

	int m_health = 3;
};

