#include "PlayerShooting.h"
#include "Input.h"
#include "Timer.h"

static const Input& input = Input::Instance();
static const Timer& timer = Timer::Instance();

static double pi = 2 * acos(0.0);
static double piRadiant = pi / 180;

static float currentTime = 1;
static float attackSpeed = 3;

static float fireRatePowerupDuration = 5.0f;
static float fireRatePowerupCurrentTime = 0;
static bool fireRatePowerupStarted = false;

void PlayerShooting::Update()
{
	Aim();

	if (input.Instance().LeftMouseDown())
		Shoot();

	if (fireRatePowerupStarted) 
	{
		if (attackSpeed != 7)
			attackSpeed = 7;

		fireRatePowerupCurrentTime += timer.ElapsedSeconds();
		if (fireRatePowerupCurrentTime >= fireRatePowerupDuration) 
		{
			fireRatePowerupStarted = false;
			fireRatePowerupCurrentTime = 0;
			attackSpeed = 3;
		}
	}
}

void PlayerShooting::StartFireRatePowerup()
{
	fireRatePowerupStarted = true;
	fireRatePowerupCurrentTime = 0;
}

void PlayerShooting::CalculateAimAngle()
{
	vec2 position = m_transform->GetPosition();
	vec2 mousePos = input.Instance().GetMousePos();

	m_aim.x = mousePos.x - position.x;
	m_aim.y = mousePos.y - position.y;

	m_aim = m_aim.normalize(m_aim) * 100;						//Multiply the aim direction 100 to change the arrow length
	m_aimAngle = ((atan2(m_aim.y, m_aim.x)) * 180) / pi;		//Convert radians to degrees
}

void PlayerShooting::Shoot()
{
	if ((currentTime * attackSpeed) > 0.4f)
	{
		currentTime = 0;
		m_snowballController->SpawnSnowball(m_aim.normalized(), m_transform->GetPosition());
	}
}

void PlayerShooting::Aim()
{
	CalculateAimAngle();

	if (currentTime < 1)
		currentTime += timer.ElapsedSeconds();
}

