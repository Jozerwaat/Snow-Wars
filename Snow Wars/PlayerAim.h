#pragma once
#include "Transform.h"
#include "Vec.h"
#include "SnowballController.h"

class PlayerAim
{
public:
	PlayerAim() = default;
	PlayerAim(Transform * transform, SnowballController& snowballController)
	{
		m_transform = transform;
		m_snowballController = &snowballController;
	}
	~PlayerAim() = default;

	float GetAimAngle() const { return m_aimAngle; }
	void Update();

private:
	void CalculateAimAngle();
	void Shoot();
	void Aim();

	SnowballController* m_snowballController;
	Transform* m_transform;
	vec2 m_aim;
	float m_aimAngle;
};