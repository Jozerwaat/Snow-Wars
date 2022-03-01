#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include "Transform.h"
#include "Renderer.h"
#include "CircleCollider.h"

class Entity
{
public:
	Entity() = default;

	Entity(vec2 position, std::string spritePath, int frameCount, vec2 size = NULL)
	{
		m_transform = Transform(position);
		m_renderer = Renderer(spritePath, frameCount, size);
		m_instantiated = true;
	}
	~Entity() {}
	
	virtual void Init() {}
	virtual void Update() {}
	virtual void SetRadius(int radius) { m_collider = CircleCollider(radius, &m_transform); }

	bool IsInstantiated() { return m_instantiated; }

	CircleCollider* GetCollider() { return &m_collider; }

	Transform* GetTransform() { return &m_transform; }

protected:
	Transform m_transform;
	Renderer m_renderer;
	CircleCollider m_collider;
	bool m_instantiated = false;
};

