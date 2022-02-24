#pragma once
#include <string>
#include "Window.h"
#include "Vec.h"

class Sprite
{
public:
	Sprite(vec2 size, const std::string& imagePath);
	~Sprite();

	inline SDL_Texture* GetTexture() { return m_texture; }
	inline vec2 GetSize() { return m_size; }

protected:

private:
	SDL_Texture* m_texture = nullptr;
	vec2 m_size = { 10,10 };
};

