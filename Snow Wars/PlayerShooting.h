#pragma once
#include "Transform.h"
#include "Vec.h"
#include "SnowballController.h"
#include "Player.h"

class PlayerShooting
{
public:
	PlayerShooting() = default;
	PlayerShooting(Transform * transform, SnowballController& snowballController, Player* player)
	{
		m_transform = transform;
		m_snowballController = &snowballController;
		m_player = player;
	}
	~PlayerShooting() = default;

	float GetAimAngle() const { return m_aimAngle; }
	void Update();
	void StartFireRatePowerup();
	void StartMultiShotPowerup();
	void SnowballBurst();
	void Reset();

private:
	void CalculateAimAngle();
	void Shoot();
	void Aim();

	Player* m_player = nullptr;
	SnowballController* m_snowballController = nullptr;
	Transform* m_transform = nullptr;
	vec2 m_aim = {};
	float m_aimAngle = 0;
};