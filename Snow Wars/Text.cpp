#include <iostream>
#include "Text.h"
#include "Window.h"


Text::Text(const std::string& fontPath, int fontSize, const std::string& messageText, const SDL_Color& color)
{
    m_texture = LoadFont(fontPath, fontSize, messageText, color);
    SDL_QueryTexture(m_texture, nullptr, nullptr, &m_textRect.w, &m_textRect.h);
}

void Text::Display(vec2 pos)
{
    m_textRect.x = pos.x;
    m_textRect.y = pos.y;

    SDL_RenderCopy(Window::m_renderer, m_texture, nullptr, &m_textRect);
}

SDL_Texture* Text::LoadFont(const std::string& fontPath, int fontSize, const std::string& messageText, const SDL_Color& color)
{
    TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);

    if (font == NULL)
        std::cerr << "Failed to load font" << std::endl;

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, messageText.c_str(), color);

    if (textSurface == NULL)
        std::cerr << "Failed to create text surface" << std::endl;
    
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Window::m_renderer, textSurface);

    if(textTexture == NULL)
        std::cerr << "Failed to create text texture" << std::endl;

    SDL_FreeSurface(textSurface);
    return textTexture;
}
