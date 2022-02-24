#pragma once
#include <SDL_ttf.h>
#include <string>
#include "Window.h"
#include "Vec.h"

class Text
{
public:
	Text(const std::string& fontPath, int fontSize, const std::string& messageText, const SDL_Color& color);

	void Display(vec2 pos);

	static SDL_Texture* LoadFont(const std::string& fontPath, int fontSize, const std::string& messageText, const SDL_Color& color);
private:
	SDL_Texture* m_texture = nullptr;
	mutable SDL_Rect m_textRect;

};

