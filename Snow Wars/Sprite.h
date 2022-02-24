#pragma once
#include <string>
#include "Window.h"
#include "Vec.h"

class Sprite
{
public:
	Sprite(vec2 size, vec2 pos, const std::string& imagePath);
	~Sprite();

	void Draw(vec2 pos);

protected:

private:
	SDL_Texture* m_texture = nullptr;
	vec2 m_size = { 10,10 };
	vec2 m_pos = { 0,0 };
};

