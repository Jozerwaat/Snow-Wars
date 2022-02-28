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
	Window* m_window;
	Transform* m_transform;
};