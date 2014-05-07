#pragma once
#include <SDL.h>
#include <vector>
#include "drawable.h"

class Window
{
public:
	Window(int width, int height);
	~Window(void);

	SDL_Window            *window;
	SDL_GLContext          context;
	int                    width;
	int                    height;
	std::vector<Drawable*> drawables;

	void AddDrawable(Drawable *d);
	void Render(void);
	void SwapBuffer(void);
};

