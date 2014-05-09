#ifndef EVENTS_H
#define EVENTS_H
#include <SDL.h>

class EventHandler
{
public:
	SDL_Event event;
	void HandleEvents();
	void KeyDown();
	void KeyUp();
	void MouseMotion();
	void MouseButtonUp(void);
	void MouseButtonDown(void);
	void ResetMouseMotion();
};

#endif
