#include "state.h"
#include <iostream>

state_t *state = NULL;

state_t *state_t::get_state(void)
{
	if(state == NULL)
	{
		state = new state_t();
	}
	return state;
}

float state_t::get_time(void)
{
	return glfwGetTime();
}

state_t::state_t(float dt)
:	window(NULL)
,	done(false)
,   dt(dt)
{
	LEFT = RIGHT = UP = DOWN = SPACE = false;
	std::fill_n(letters, 26, false);

	if(glfwInit())
	{
		window = glfwCreateWindow(scale * width , scale * height, "Game", NULL, NULL);
		glfwMakeContextCurrent(window);
	}

	glfwSetWindowSizeCallback(window, state_t::window_size_callback);
	glfwSetKeyCallback(window, state_t::key_callback);
	float aspect = (float)width / (float)height;
	std::cout << "Aspect ratio:" << aspect << std::endl;
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0,height, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gravity[1] =  0.0f;
	gravity[1] = -900.0f;

#if WIREFRAME	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif

#if !SHOW_MOUSE
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
#endif
}
bool state_t::is_done(void)
{
	return done || glfwWindowShouldClose(window);
}

#define X(key, b) case GLFW_KEY_ ## key:state->key = b;break
void state_t::key_callback(GLFWwindow *window, int key, int scan_code, int action, int mods)
{
	if(key >= 'A' && key <= 'Z')
	{
		if(action == GLFW_PRESS)
		{
			state->letters[key - 'A'] = true;
		}
		else if(action == GLFW_RELEASE)
		{
			state->letters[key - 'A'] = false;
		}
	}
	if(action == GLFW_PRESS)
	{
		switch(key)
		{
			X(SPACE, true);
			X(UP,    true);
			X(LEFT,  true);
			X(DOWN,  true);
			X(RIGHT, true);
		}
	}
	if(action == GLFW_RELEASE)
	{
		switch(key)
		{
			X(SPACE, false);
			X(UP,    false);
			X(LEFT,  false);
			X(DOWN,  false);
			X(RIGHT, false);
		}
	}
}
#undef X
void state_t::window_size_callback(GLFWwindow *window, int width, int height)
{
	float new_width = aspect * height;
	float new_height;
	float excess;
	if(new_width <= width)
	{
		excess = (width - new_width) / 2;
		glViewport(excess,0,new_width, height);
	}
	else
	{
		new_height = width / aspect;
		excess = (height - new_height) / 2;
		glViewport(0, excess, width, new_height);
	}
}

void state_t::process_events(void)
{
	glfwPollEvents();
	double x,y;
}

void state_t::add(object_t *obj)
{
	objects.push_back(obj);
}

void state_t::simulate(void)
{
	for(int i = 0; i < objects.size(); i++)
	{
		objects[i]->pre_simulate();
		objects[i]->simulate(*this);
	}
}

//Draws the game grid
void state_t::draw_grid(void)
{
#if !WIREFRAME
	int grid_width  = 100;
	int grid_height = 100;
	glPushMatrix();
	glLoadIdentity();
	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 0.0);
	for(int i = 1; i < (width / grid_width); i++)
	{
		glVertex2i(i * grid_width, 0);
		glVertex2i(i * grid_width, height);
	}

	for(int i = 1; i < (height / grid_height); i++)
	{
		glVertex2i(0, i* grid_height);
		glVertex2i(width,i * grid_height);
	}
	glEnd();
	glPopMatrix();
#endif
}

void state_t::render(void)
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glBegin(GL_QUADS);
		glColor3f(0.3, 0.3, 0.3);
		glVertex2i(0,0);
		glVertex2i(width,0);
		glVertex2i(width,height);
		glVertex2i(0,height);
	glEnd();
	draw_grid();
	for(int i = 0; i < objects.size(); i++)
	{
		objects[i]->pre_draw();
		objects[i]->draw();
		objects[i]->post_draw();
	}
	glfwSwapBuffers(window);
}

