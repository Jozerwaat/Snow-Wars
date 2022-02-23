#include <iostream>
#include "Window.h"

Window::Window(std::string title, int width, int height) :
	m_title(title), m_width(width), m_height(height)
{
	m_closed = !Init();
}

Window::~Window()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}


bool Window::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != NULL)
	{
		std::cout << "Failed to intialize SDL." << std::endl;
		return false;
	}

	m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, 0);

	if (m_window == nullptr)
	{
		std::cerr << "Failed to create window. ";
		return false;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

	if (m_renderer == nullptr)
	{
		std::cerr << "Failed to create renderer.";
		return false;
	}
	return true;
}

void Window::PollEvents()
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_closed = true;
			break;

		default:
			break;
		}
	}
}

void Window::Clear() const
{
	SDL_SetRenderDrawColor(m_renderer, 110, 110, 110, 255);
	SDL_RenderClear(m_renderer);

	SDL_Rect rect;
	rect.w = 100;
	rect.h = 100;
	rect.x = (m_width / 2) - (rect.w / 2);
	rect.y = (m_height / 2) - (rect.h /2);
	
	SDL_SetRenderDrawColor(m_renderer, 200, 0, 200, 255);
	SDL_RenderFillRect(m_renderer, &rect);

	SDL_RenderPresent(m_renderer);
}