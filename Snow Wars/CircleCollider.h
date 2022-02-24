#pragma once
#include "Transform.h"

class CircleCollider
{
public:
	CircleCollider() = default;

	CircleCollider(int radius, Transform* transform)
	{
		m_radius = radius;
		m_transform = transform;
	}

	inline Transform* GetTransform() { return m_transform;}
	
	bool IsColliding(CircleCollider* other);

private:
	Transform* m_transform = nullptr;
	int m_radius = 1;
};

