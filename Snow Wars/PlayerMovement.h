#pragma once
#include "Transform.h"
#include "Vec.h"

class PlayerMovement
{
public:
	PlayerMovement() = default;
	PlayerMovement(Transform transform) { m_transform; }

	void ClipBorder();
	void Move();

private:
	Transform m_transform;
};