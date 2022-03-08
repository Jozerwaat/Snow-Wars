#include "SnowballController.h"
#include "ObjectPool.h"

static std::string spritePath = "Assets/Snowball.png";
static int speed = 1000;

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
		*snowball = Snowball(position, spritePath, 1);

	snowball->SetRadius(22);

	snowball->InitSpawnedEnemy(position, direction, speed);
}

void SnowballController::PoolSnowball(int i)
{
	objectPool.Pool(m_snowballs[i]);
	m_snowballs.erase(m_snowballs.begin() + i);
}

void SnowballController::PoolAll()
{
	for (int i = m_snowballs.size() - 1; i >= 0; i--)
	{
		objectPool.Pool(m_snowballs[i]);
		m_snowballs.pop_back();
	}
}