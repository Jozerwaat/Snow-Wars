#include "PlayerMovement.h"
#include "Input.h"
#include "Timer.h"

static const Input& input = Input::Instance();
static const Timer& timer = Timer::Instance();

static int speed = 300;

void PlayerMovement::Move()
{
	vec2 movement = vec2(0, 0);

	if (input.Instance().KeyboardEvents()[SDL_SCANCODE_W])
		movement.y = -1;
	if (input.Instance().KeyboardEvents()[SDL_SCANCODE_A])
		movement.x = -1;
	if (input.Instance().KeyboardEvents()[SDL_SCANCODE_S])
		movement.y = 1;
	if (input.Instance().KeyboardEvents()[SDL_SCANCODE_D])
		movement.x = 1;

	if (movement.x == 0 && movement.y == 0)
		return;

	m_transform->Translate((movement.normalized() * speed) * timer.ElapsedSeconds());
	ClipBorder();
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