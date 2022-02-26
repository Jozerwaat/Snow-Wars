#pragma once
#include "Entity.h"
#include "Window.h"

class SnowballController;
class Transform;

class Player : public Entity
{
public:
	Player() = default;

	Player(Window* window, vec2 position, std::string spritePath, int frameCount, vec2 size = NULL) : Entity(position, spritePath, frameCount, size) 
	{
		m_window = window;
	}

	void Update() override;

	Transform GetTransform() const { return m_transform; }

	void Init(SnowballController& snowballController);

private:
	void CalculateAimAngle();
	void Move();
	void Shoot();
	void Aim();

	Window* m_window;
	int m_health = 3;
};

