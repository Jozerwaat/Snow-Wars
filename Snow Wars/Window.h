#pragma once
#include <string>
#include <SDL.h>

class Window
{
public:
	
	Window(std::string title, int width, int height);
	
	~Window();

	void PollEvents();
	void Clear() const;

	inline bool IsClosed() const { return m_closed; }

private:
	bool Init();


	std::string m_title = "Snow Wars";
	int m_width = 800;
	int m_height = 600;
	bool m_closed = false;

	SDL_Window* m_window = nullptr;
	SDL_Renderer* m_renderer = nullptr;
};