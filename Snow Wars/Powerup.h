#pragma once
#include "Entity.h"

enum class POWERUP_TYPE;

enum class POWERUP_TYPE
{
	FIRE_RATE = 0,
	MULTI_SHOT = 1
};


class Powerup : public Entity
{

public:
	Powerup() = default;
	Powerup(vec2 position, std::string spritePath, int frameCount, vec2 size = NULL) : Entity(position, spritePath, frameCount, size) {}
	~Powerup() = default;

	void Update();
	float GetDuration() const { return m_duration; }

	POWERUP_TYPE GetPowerUpType() { return m_type; }
	void SetType(POWERUP_TYPE type) { m_type = type; }
private:
	float m_duration;
	POWERUP_TYPE m_type;
	std::string m_spritePath = "";
};

