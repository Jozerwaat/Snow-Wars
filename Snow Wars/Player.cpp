#pragma once
#include <SDL.h>
#include "player.h"
#include "game.h"
#include "Timer.h"
#include "SnowballController.h"
#include "Input.h"
#include "PlayerMovement.h"
#include "PlayerShooting.h"

static const Timer& timer = Timer::Instance();

PlayerMovement playerMovement;
PlayerShooting playerShooting;

static float invincibilityDuration = 3;
static float invincibilityTime = 0;
static float visibilityTime = 0.2f;
static bool spritevisible = false;

void Player::InitSpawnedEnemy(SnowballController& controller)
{
	playerMovement.~PlayerMovement();
	playerShooting.~PlayerShooting();
	playerMovement = PlayerMovement(&m_transform, m_window);
	playerShooting = PlayerShooting(&m_transform, controller, this);

	SetRadius(22);
}
void Player::TakeDamage()
{
	if (m_isInvincible)
		return;

	playerShooting.SnowballBurst();
	m_health--;
	m_isInvincible = true;
	invincibilityTime = 0;
}
void Player::Reset()
{
	m_health = 3;
	m_isInvincible = false;
	invincibilityDuration = 3;
	invincibilityTime = 0;
	visibilityTime = 0.2f;
	spritevisible = false;
	playerShooting.Reset();
}
void Player::StartPowerUp(POWERUP_TYPE type)
{
	if (type == POWERUP_TYPE::FIRE_RATE)
		playerShooting.StartFireRatePowerup();
	if (type == POWERUP_TYPE::MULTI_SHOT)
		playerShooting.StartMultiShotPowerup();
}
void Player::Update()
{
	if (m_isInvincible)
	{
		invincibilityTime += timer.ElapsedSeconds();

		if (invincibilityTime > visibilityTime)
		{
			visibilityTime += 0.2f;
			spritevisible = !spritevisible;
		}
		if(spritevisible)
			m_renderer.Render(m_transform.GetPosition(), playerShooting.GetAimAngle() + 90);

		if (invincibilityTime >= invincibilityDuration) 
		{
			m_isInvincible = false;
			spritevisible = false;
			visibilityTime = 0.2f;
		}
	}
	else
	{
		m_renderer.Render(m_transform.GetPosition(), playerShooting.GetAimAngle() + 90);
	}
	m_renderer.Animate(40, true);
	playerMovement.Move();
	playerShooting.Update();
}