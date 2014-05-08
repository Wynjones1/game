#include "events.h"
#include "input_state.h"
#include <iostream>

void EventHandler::KeyUp()
{
	switch(event.key.keysym.sym)
	{
	case SDLK_UP:
		g_input_state.up    = false;
		break;
	case SDLK_DOWN:
		g_input_state.down  = false;
		break;
	case SDLK_LEFT:
		g_input_state.left  = false;
		break;
	case SDLK_RIGHT:
		g_input_state.right = false;
	case SDLK_SPACE:
		g_input_state.space_key = false;
		break;
	}

	if(event.key.keysym.sym >= 'a' && event.key.keysym.sym <= 'z')
	{
		g_input_state.SetLetterPressed(event.key.keysym.sym, false);
	}
}

void EventHandler::KeyDown()
{
	switch(event.key.keysym.sym)
	{
	case SDLK_ESCAPE:
		exit(0);
	case SDLK_UP:
		g_input_state.up    = true;
		break;
	case SDLK_DOWN:
		g_input_state.down  = true;
		break;
	case SDLK_LEFT:
		g_input_state.left  = true;
		break;
	case SDLK_RIGHT:
		g_input_state.right = true;
		break;
	case SDLK_SPACE:
		g_input_state.space_key = true;
		break;
	}

	if(event.key.keysym.sym >= 'a' && event.key.keysym.sym <= 'z')
	{
		g_input_state.SetLetterPressed(event.key.keysym.sym, true);
	}
}

void EventHandler::MouseMotion()
{
	g_input_state.mouse_rot[0] = (float) -event.motion.xrel;
	g_input_state.mouse_rot[1] = (float) event.motion.yrel;
}

void EventHandler::ResetMouseMotion()
{
	g_input_state.mouse_rot[0] = 0;
	g_input_state.mouse_rot[1] = 0;
}
void EventHandler::HandleEvents()
{
	ResetMouseMotion();
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
		case SDL_QUIT:
			exit(0);
		case SDL_KEYDOWN:
			KeyDown();
			break;
		case SDL_KEYUP:
			KeyUp();
			break;
		case SDL_MOUSEMOTION:
			MouseMotion();
			break;
		}
	}
}