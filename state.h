#ifndef STATE_H
#define STATE_H
#include <vector>
#include <GLFW/glfw3.h>
#include "object.h"
#define SECOND SCALE

class state_t
{
public:
	state_t(float dt = 0.01);
	void simulate(void);
	void render(void);
	void process_events(void);
	void add(object_t *obj);
	bool is_done(void);
	void draw_grid(void);

	std::vector<object_t*> objects;

	GLFWwindow *window;
	bool        done;
	float dt;
	static const int width     = 1600;
	static const int height    = 1000;
	constexpr static const float scale   = 0.5;
	constexpr static const float aspect  = (float)width / height;
	
	static float get_time(void);
	/*
	*	These are the callback functions to respond to events.
	*/
	static void key_callback(GLFWwindow *window, int key, int scan_code, int action, int mods);
	static void window_size_callback(GLFWwindow *window, int width, int height);

	static state_t *get_state(void);
	bool letters[26];
	bool LEFT, RIGHT, UP, DOWN, SPACE;

	float gravity[2];
};

#endif
