#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Window.h"

SDL_Renderer* Window::m_renderer = nullptr;

Window::Window(std::string title, int width, int height) :
	m_title(title), m_width(width), m_height(height)
{
	m_closed = !Init();
	std::cout << "Window Initialized!" << std::endl;
}

Window::~Window()
{
	std::cout << "Destroy window!" << std::endl;
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}


bool Window::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != NULL)
	{
		std::cerr << "Failed to intialize SDL." << std::endl;
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG) != 2)
	{
		std::cerr << "Failed to initialize image." << std::endl;
		return false;
	}

	if (TTF_Init() == -1)
	{
		std::cerr << "Failed to initialize ttf." << std::endl;
		return false;
	}

	m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_SHOWN);

	if (m_window == nullptr)
	{
		std::cerr << "Failed to create window. ";
		return false;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);

	if (m_renderer == nullptr)
	{
		std::cerr << "Failed to create renderer.";
		return false;
	}

	m_initialized = true;
	return true;
}


void Window::Render() const
{
	SDL_RenderPresent(m_renderer);
	SDL_SetRenderDrawColor(m_renderer, 110, 110, 110, 255);
	SDL_RenderClear(m_renderer);
}

void Window::Resize()
{
	if (m_fullscreen == false)
	{
		SDL_MaximizeWindow(m_window);
		SDL_GetWindowSize(m_window, &m_width, &m_height);
		SDL_GLContext context = SDL_GL_CreateContext(m_window);
		SDL_GL_MakeCurrent(m_window, context);
		m_fullscreen = true;
	}
	else if (m_fullscreen)
	{
		SDL_RestoreWindow(m_window);
		SDL_GetWindowSize(m_window, &m_width, &m_height);
		SDL_GLContext context = SDL_GL_CreateContext(m_window);
		SDL_GL_MakeCurrent(m_window, context);
		m_fullscreen = false;
	}
}