#pragma once
#include <string>
#include <SDL.h>

class Window
{
public:

	Window(std::string title, int width, int height);
	~Window();

	void Close() { m_closed = true; }
	void Render() const;
	
	inline bool Initalized() { return m_initialized; }

	inline int GetScreenWidth() const { return m_width; }

	inline int GetScreenHeight() const { return m_height; }

	inline bool IsClosed() const { return m_closed; }

	static SDL_Renderer* m_renderer;

protected:

private:
	bool Init();

	std::string m_title = "Snow Wars";
	int m_width = 800;
	int m_height = 600;
	bool m_closed = false;
	bool m_initialized = false;

	SDL_Window* m_window = nullptr;
};