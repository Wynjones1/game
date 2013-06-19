#include <containers/list.h>
#include <stdio.h>
#include <GL/gl.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "sleep.h"
#include "state.h"
#include "callbacks.h"
#include "init.h"
#include "draw.h"
#include "simulate.h"
#include "ball.h"

#define min(a , b) (a) < (b) ? (a) : (b)
#define max(a , b) (a) > (b) ? (a) : (b)

static state_t new_state;
static state_t old_state;

void render(state_t *new, state_t *old, float diff)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	draw(new);
	glfwSwapBuffers(new->window);
}

int main(void)
{

	new_state.window = init();
	state_init(&new_state);
	callbacks_register_state(&new_state, &old_state);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	float dt          = 0.001;
	float t           = 0.0;
	float curr_time   = glfwGetTime();
	float frame_max   = 0.25;
	float new_time, frame_time, accum = 0.0;

	object_t *ball = ball_new(10);
	state_add_object(&new_state, ball);

	simulate(&new_state, t, dt);

	while(!glfwWindowShouldClose(new_state.window))
	{
		new_time   = glfwGetTime();
		frame_time = new_time - curr_time;
		if(frame_time > frame_max)
			frame_time = frame_max;

		curr_time = new_time;

		accum += frame_time;
		while(accum >= dt)
		{
			simulate(&new_state, t, dt);
			t += dt;
			accum -= dt;
		}
		float alpha = accum / dt;
		render(&new_state, &old_state, alpha);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
