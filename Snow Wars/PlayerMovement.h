#pragma once
#include "Transform.h"
#include "Vec.h"
#include "Window.h"

class PlayerMovement
{
public:
	PlayerMovement() = default;
	PlayerMovement(Transform* transform, Window* window) 
	{ 
		m_transform = transform; 
		m_window = window;
	}
	~PlayerMovement() = default;

	void ClipBorder();
	void Move();
	void Dash();
private:
	vec2 m_moveDirection = { 0,0 };
	vec2 m_dashDirection = { 0,0 };
	Window* m_window;
	Transform* m_transform;
	bool m_dashStarted = false;
	float m_dashCooldown = 0.5f;
	float m_currenTime = 0;
	float m_dashTime = 0;
	float m_dashDuration = 0.15f;
};