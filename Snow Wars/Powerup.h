#pragma once
#include "Entity.h"
class Powerup : public Entity
{
public:
	Powerup() = default;
	Powerup(vec2 position, std::string spritePath, int frameCount, vec2 size = NULL) : Entity(position, spritePath, frameCount, size) {}
	~Powerup() = default;
	
	void Update();

private:

};