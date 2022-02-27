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

private:
	Window* m_window;
	Transform* m_transform;
};