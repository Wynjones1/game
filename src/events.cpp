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

void EventHandler::MouseButtonUp(void)
{
	switch(event.button.button)
	{
		case SDL_BUTTON_LEFT:
			g_input_state.mouse_buttons[0] = 0;
			break;
		case SDL_BUTTON_MIDDLE:
			g_input_state.mouse_buttons[1] = 0;
			break;
		case SDL_BUTTON_RIGHT:
			g_input_state.mouse_buttons[2] = 0;
			break;
	}
}

void EventHandler::MouseButtonDown(void)
{
	switch(event.button.button)
	{
		case SDL_BUTTON_LEFT:
			g_input_state.mouse_buttons[0] = 1;
			break;
		case SDL_BUTTON_MIDDLE:
			g_input_state.mouse_buttons[1] = 1;
			break;
		case SDL_BUTTON_RIGHT:
			g_input_state.mouse_buttons[2] = 1;
			break;
	}
}

void EventHandler::GameControllerButton(bool down)
{
	switch(event.cbutton.button)
	{
		case 0:
			g_input_state.a = down;
			break;
		case 1:
			g_input_state.b = down;
			break;
		case 2:
			g_input_state.x = down;
			break;
		case 3:
			g_input_state.y = down;
			break;
		case 4:
			g_input_state.back = down;
			break;
		case 5:
			g_input_state.xbox = down;
			break;
		case 6:
			g_input_state.start = down;
			break;
		case 7:
			g_input_state.lstick = down;
			break;
		case 8:
			g_input_state.rstick= down;
			break;
		case 9:
			g_input_state.lb = down;
			break;
		case 10:
			g_input_state.rb = down;
			break;
		case 11:
			g_input_state.dpad[0] = down;
			break;
		case 12:
			g_input_state.dpad[1] = down;
			break;
		case 13:
			g_input_state.dpad[2] = down;
			break;
		case 14:
			g_input_state.dpad[3] = down;
			break;
		default:
			std::cout << (int)event.cbutton.button << std::endl;
			break;
	}
}

void EventHandler::GameControllerAxis(void)
{
	float value = (float)event.caxis.value / 32768;
	switch(event.caxis.axis)
	{
		case 0:
			g_input_state.laxis[0] = value;
			break;
		case 1:
			g_input_state.laxis[1] = value;
			break;
		case 2:
			g_input_state.raxis[0] = value;
			break;
		case 3:
			g_input_state.raxis[1] = value;
			break;
		case 4:
			g_input_state.ltrigger = value;
			break;
		case 5:
			g_input_state.rtrigger = value;
			break;
		default:
			break;
	}
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
		case SDL_MOUSEBUTTONUP:
			MouseButtonUp();
			break;
		case SDL_MOUSEBUTTONDOWN:
			MouseButtonDown();
			break;
		case SDL_CONTROLLERBUTTONDOWN:
			GameControllerButton(true);
			break;
		case SDL_CONTROLLERBUTTONUP:
			GameControllerButton(false);
			break;
		case SDL_CONTROLLERAXISMOTION:
			GameControllerAxis();
			break;
		}
	}
}

SDL_GameController *g_game_controller;
