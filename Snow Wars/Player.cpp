#pragma once
#include <SDL.h>
#include "player.h"
#include "game.h"
#include "Timer.h"
#include "SnowballController.h"
#include "Input.h"

const static Input& playerInput = Input::Instance();

vec2 aim;

int speed = 300;
float aimAngle = -90;
float arrowLength = 100;
float attackSpeed = 3;
float currentTime = 1;
//extern float deltaTime;

double pi = 2 * acos(0.0);
double piRadiant = pi / 180;

bool mouseMovement = true;
SnowballController* snowballController;
static const Timer& timer = Timer::Instance();

void Player::Init(SnowballController& controller)
{
	snowballController = &controller;
	SetRadius(22);
}
void Player::Update()
{
	m_renderer.Render(m_transform.GetPosition(), aimAngle + 90);

	Move();
	Aim();

	if (playerInput.Instance().MouseDown())
		Shoot();
}

void Player::CalculateAimAngle()
{
	vec2 position = m_transform.GetPosition();
	vec2 mousePos = playerInput.Instance().GetMousePos();

	if (mouseMovement)
	{
		aim.x = mousePos.x - position.x;
		aim.y = mousePos.y - position.y;

		aim = aim.normalize(aim) * 100;						//Multiply the aim direction 100 to change the arrow length
		aimAngle = ((atan2(aim.y, aim.x)) * 180) / pi;		//Convert radians to degrees
	}
	else
	{
		aim.x = arrowLength * cos(aimAngle * piRadiant);
		aim.y = arrowLength * sin(aimAngle * piRadiant);
	}
}

void Player::Move()
{
	vec2 movement = vec2(0, 0);

	if (playerInput.Instance().KeyboardEvents()[SDL_SCANCODE_W])
		movement.y = -1;
	if (playerInput.Instance().KeyboardEvents()[SDL_SCANCODE_A])
		movement.x = -1;
	if (playerInput.Instance().KeyboardEvents()[SDL_SCANCODE_S])
		movement.y = 1;
	if (playerInput.Instance().KeyboardEvents()[SDL_SCANCODE_D])
		movement.x = 1;

	if (movement.x == 0 && movement.y == 0)
		return;

	m_transform.Translate((movement.normalized() * speed) * timer.ElapsedSeconds());
}

void Player::Shoot()
{
	if ((currentTime * attackSpeed) > 0.4f)
	{
		currentTime = 0;
		snowballController->SpawnSnowball(aim.normalized(), m_transform.GetPosition());
	}
}

void Player::Aim()
{
	CalculateAimAngle();

	if (currentTime < 1)
		currentTime += timer.ElapsedSeconds();
}

