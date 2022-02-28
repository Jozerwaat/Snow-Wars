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

	if (m_moveDirection.x == 0 && m_moveDirection.y == 0)
		return;

	m_transform->Translate((m_moveDirection.normalized() * speed) * timer.ElapsedSeconds());
	ClipBorder();
}

void PlayerMovement::Dash()
{
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