#pragma once
#include "Vec.h"

class Transform
{
public:

	Transform() = default;

	Transform(vec2 position)
	{
		m_position = position;
	}

	vec2& GetPosition()
	{
		return m_position;
	}

	void Translate(vec2 direction) { m_position += direction; }

protected:
	vec2 m_position;
};

