#include "PlayerMovement.h"
#include "Input.h"
#include "Timer.h"

static const Input& input = Input::Instance();
static const Timer& timer = Timer::Instance();

static int speed = 300;

void PlayerMovement::Move()
{
	m_moveDirection = vec2(0, 0);

	if (input.Instance().KeyboardEvents()[SDL_SCANCODE_W])
		m_moveDirection.y = -1;
	if (input.Instance().KeyboardEvents()[SDL_SCANCODE_A])
		m_moveDirection.x = -1;
	if (input.Instance().KeyboardEvents()[SDL_SCANCODE_S])
		m_moveDirection.y = 1;
	if (input.Instance().KeyboardEvents()[SDL_SCANCODE_D])
		m_moveDirection.x = 1;

	Dash();


	ClipBorder();
	if (m_moveDirection.x == 0 && m_moveDirection.y == 0)
		return;

	if (m_dashStarted == false)
		m_transform->Translate((m_moveDirection.normalized() * speed) * timer.ElapsedSeconds());

}

void PlayerMovement::Dash()
{
	if (m_dashStarted == false)
		m_currenTime += timer.ElapsedSeconds();
	else 
	{
		m_transform->Translate((m_dashDirection.normalized() * speed * 3) * timer.ElapsedSeconds());
		m_dashTime += timer.ElapsedSeconds();
	}
	if (m_dashTime >= m_dashDuration)
	{
		m_dashTime = 0;
		m_dashStarted = false;
		m_currenTime = 0;
	}

	if (input.Instance().RightMouseDown())
	{
		if (m_moveDirection.x == 0 && m_moveDirection.y == 0)
			return;
		if (m_dashStarted == false && m_currenTime > m_dashCooldown)
		{
			m_dashDirection = m_moveDirection;
			m_dashStarted = true;
			m_currenTime = 0;
			m_dashTime = 0;
		}
	}
}

void PlayerMovement::ClipBorder()
{
	if (m_transform->GetPosition().x >= (m_window->GetWidth() - 45))
		m_transform->GetPosition().x = m_window->GetWidth() - 45;

	if (m_transform->GetPosition().x <= (45))
		m_transform->GetPosition().x = 45;

	if (m_transform->GetPosition().y >= (m_window->GetHeight() - 45))
		m_transform->GetPosition().y = m_window->GetHeight() - 45;

	if (m_transform->GetPosition().y <= (45))
		m_transform->GetPosition().y = 45;
}