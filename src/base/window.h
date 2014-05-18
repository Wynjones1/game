#pragma once
#include <SDL.h>
#include <vector>

class Window
{
public:
	Window(int width, int height);
	~Window(void);

	SDL_Window            *window;
	SDL_GLContext          context;
	int                    width;
	int                    height;

	void SwapBuffer(void);
};

