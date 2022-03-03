#pragma once
#include <SDL.h>
#include "player.h"
#include "game.h"
#include "Timer.h"
#include "SnowballController.h"
#include "Input.h"
#include "PlayerMovement.h"
#include "PlayerShooting.h"
PlayerMovement playerMovement;
PlayerShooting playerShooting;


void Player::Init(SnowballController& controller)
{
	playerMovement.~PlayerMovement();
	playerShooting.~PlayerShooting();
	playerMovement = PlayerMovement(&m_transform, m_window);
	playerShooting = PlayerShooting(&m_transform, controller);

	SetRadius(22);
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
	m_renderer.Render(m_transform.GetPosition(), playerShooting.GetAimAngle() + 90);
	m_renderer.Animate(40, true);
	playerMovement.Move();
	playerShooting.Update();
}