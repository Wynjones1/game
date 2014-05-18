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
	void GameControllerButton(bool down);
	void GameControllerAxis(void);
};

extern SDL_GameController *g_game_controller;
#endif
