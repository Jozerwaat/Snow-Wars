#pragma once
#include <vector>
#include "Snowball.h"
#include "Window.h"

class SnowballController
{
public:
	SnowballController(Window& window) { m_window = &window; }

	void UpdateSnowballs();
	void SpawnSnowball(vec2 direction, vec2 snowmanPos);

	std::vector<Snowball*> GetSnowballs() { return m_snowballs; }

	void PoolSnowball(int index);
	void PoolAll();
private:
	std::vector<Snowball*> m_snowballs;
	Window* m_window = nullptr;
};