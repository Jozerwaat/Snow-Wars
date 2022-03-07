#pragma once
#include <string>
#include "Window.h"
#include "Vec.h"

class Sprite
{
public:
	Sprite() = default;
	Sprite(const std::string& imagePath, vec2 size = NULL);
	~Sprite();

	inline SDL_Texture* GetTexture() { return m_texture; }
	inline vec2 GetSize() { return m_size; }

protected:

private:
	SDL_Texture* m_texture = nullptr;
	vec2 m_size = { 10,10 };
};

