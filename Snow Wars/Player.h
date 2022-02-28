#pragma once
#include "Entity.h"
#include "Window.h"
#include "Powerup.h"

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

	void Init(SnowballController& snowballController);

	inline void SetHealth(int health) { m_health = health; }
	inline int& GetHealth() { return m_health; }

	inline void TakeDamage() { m_health--; }

	void StartPowerUp(POWERUP_TYPE type);
private:
	Window* m_window;
	int m_health = 3;
};

