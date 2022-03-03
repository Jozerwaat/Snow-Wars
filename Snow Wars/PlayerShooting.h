#pragma once
#include "Transform.h"
#include "Vec.h"
#include "SnowballController.h"

class PlayerShooting
{
public:
	PlayerShooting() = default;
	PlayerShooting(Transform * transform, SnowballController& snowballController)
	{
		m_transform = transform;
		m_snowballController = &snowballController;
	}
	~PlayerShooting() = default;

	float GetAimAngle() const { return m_aimAngle; }
	void Update();
	void StartFireRatePowerup();
	void StartMultiShotPowerup();
	void Reset();

private:
	void CalculateAimAngle();
	void Shoot();
	void Aim();

	SnowballController* m_snowballController;
	Transform* m_transform;
	vec2 m_aim;
	float m_aimAngle = 0;
};