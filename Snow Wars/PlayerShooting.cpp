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

static float multiShotPowerupDuration = 8.0f;
static float multiShotPowerupCurrentTime = 0;
static bool multiShotPowerupStarted = false;

static Renderer fireRateRenderer("assets/FireRatePowerupCooldown.png",8);
static Renderer multiShotRenderer("assets/MultiShotPowerupCooldown.png", 8);

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
		fireRateRenderer.Render(vec2(m_player->GetTransform()->GetPosition().x, m_player->GetTransform()->GetPosition().y - 60));
		fireRateRenderer.Animate(8 / fireRatePowerupDuration,false,false);

		if (fireRatePowerupCurrentTime >= fireRatePowerupDuration)
		{
			fireRatePowerupStarted = false;
			fireRatePowerupCurrentTime = 0;
			attackSpeed = 3;
		}
	}

	if (multiShotPowerupStarted)
	{
		multiShotPowerupCurrentTime += timer.ElapsedSeconds();
		multiShotRenderer.Render(vec2(m_player->GetTransform()->GetPosition().x, m_player->GetTransform()->GetPosition().y + 60));
		multiShotRenderer.Animate(8 / multiShotPowerupDuration, false, false);
	
		if (multiShotPowerupCurrentTime >= multiShotPowerupDuration)
		{
			multiShotPowerupStarted = false;
			multiShotPowerupCurrentTime = 0;
		}
	}
}

void PlayerShooting::StartFireRatePowerup()
{
	fireRatePowerupStarted = true;
	fireRatePowerupCurrentTime = 0;
	fireRateRenderer.SetFrame(0);
}

void PlayerShooting::StartMultiShotPowerup()
{
	multiShotPowerupStarted = true;
	multiShotPowerupCurrentTime = 0;
	multiShotRenderer.SetFrame(0);
}

void PlayerShooting::Reset()
{
	fireRatePowerupStarted = false;
	fireRatePowerupCurrentTime = 0;
	attackSpeed = 3;
	multiShotPowerupStarted = false;
	multiShotPowerupCurrentTime = 0;
}

void PlayerShooting::CalculateAimAngle()
{
	vec2 position = m_transform->GetPosition();
	vec2 mousePos = input.Instance().GetMousePos();

	m_aim.x = mousePos.x - position.x;
	m_aim.y = mousePos.y - position.y;

	m_aim = m_aim.normalize(m_aim);
	m_aimAngle = (((atan2(-m_aim.y, -m_aim.x)) * 180) / pi ) + 180;		//Convert radians to 360 degrees, negate the x and y and add 180 to get a 360 angle
}

void PlayerShooting::Shoot()
{
	if ((currentTime * attackSpeed) > 0.4f)
	{
		currentTime = 0;

		if (multiShotPowerupStarted == false)
			m_snowballController->SpawnSnowball(m_aim.normalized(), m_transform->GetPosition());
		else if(multiShotPowerupStarted)
		{
			float angleOffset = -15.0f;
			for (int i = 0; i < 3; i++)
			{
				vec2 directionOffset = { 0,0 };
				directionOffset.x = cos((m_aimAngle + angleOffset) * piRadiant);
				directionOffset.y = sin((m_aimAngle + angleOffset) * piRadiant);
				angleOffset += 15.0f;
				m_snowballController->SpawnSnowball(directionOffset, m_transform->GetPosition());

			}
		}
	}
}

void PlayerShooting::Aim()
{
	CalculateAimAngle();

	if (currentTime < 1)
		currentTime += timer.ElapsedSeconds();
}

