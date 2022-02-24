#include <string>
#include "SnowballController.h"
#include "ObjectPool.h"
static std::string spritePath = "Assets/Snowball.png";
static int speed = 800;

static ObjectPool<Snowball> objectPool;

void SnowballController::UpdateSnowballs()
{
	for (int i = 0; i < m_snowballs.size(); i++)
	{
		m_snowballs[i]->Update();

		if (m_snowballs[i]->OutsideBounds(m_window->GetWidth(), m_window->GetHeight()))
		{
			objectPool.Pool(m_snowballs[i]);
			m_snowballs.erase(m_snowballs.begin() + i);
			i--;
			continue;
		}
	}
}

void SnowballController::SpawnSnowball(vec2 direction, vec2 position)
{
	Snowball* snowball = objectPool.Get();
	m_snowballs.push_back(snowball);

	if (snowball->IsInstantiated() == false)
		*snowball = Snowball(position, vec2(50, 50), spritePath);

	snowball->SetRadius(22);

	snowball->Init(position, direction, speed);
}

void SnowballController::PoolSnowball(int i)
{
	objectPool.Pool(m_snowballs[i]);
	m_snowballs.erase(m_snowballs.begin() + i);
}
