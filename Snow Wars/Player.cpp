#pragma once
#include <SDL.h>
#include "player.h"
#include "game.h"
#include "Timer.h"
#include "SnowballController.h"
#include "Input.h"
#include "PlayerMovement.h"
#include "PlayerAim.h"

PlayerMovement playerMovement;
PlayerAim playerAim;

void Player::Init(SnowballController& controller)
{
	playerMovement.~PlayerMovement();
	playerAim.~PlayerAim();
	playerMovement = PlayerMovement(&m_transform, m_window);
	playerAim = PlayerAim(&m_transform, controller);

	SetRadius(22);
}
void Player::Update()
{
	m_renderer.Render(m_transform.GetPosition(), playerAim.GetAimAngle() + 90);
	m_renderer.Animate(40, true);
	playerMovement.Move();
	playerAim.Update();
}