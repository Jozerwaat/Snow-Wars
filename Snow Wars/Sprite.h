#pragma once
#include <string>
#include "Window.h"
#include "Vec.h"

class Sprite
{
public:
	Sprite(vec2 size, vec2 pos, const std::string& imagePath);
	~Sprite();

	void Draw() const;

protected:

private:
	SDL_Texture* m_texture = nullptr;
	vec2 m_size;
	vec2 m_pos;
};

