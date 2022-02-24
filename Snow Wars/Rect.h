#pragma once
#include <string>
#include "Window.h"
#include "Vec.h"
class Rect
{
public:
	Rect(vec2 size, vec2 pos, int r, int g, int b, int a);
	Rect(vec2 size, vec2 pos, const std::string& imagePath);
	~Rect();

	void Draw() const;

protected:

private:
	SDL_Texture* m_texture = nullptr;
	vec2 m_size;
	vec2 m_pos;
	int m_r, m_g, m_b, m_a;
};

