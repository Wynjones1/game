#pragma once
/*
*	These are configs that cannot change once the game
*	has started.
*/

struct Config
{
	int width, height;
	float aspect, fov;

	Config();
	Config(int argc, char **argv);
};

extern Config g_config;