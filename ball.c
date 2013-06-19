#include "ball.h"
#include <stdlib.h>
#include "state.h"

void ball_draw(void *data, state_t *state)
{
	ball_t *ball = data;
	glPointSize(20);
	glPushMatrix();
	glBegin(GL_POINTS);
	glVertex3f(0, 0, 0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3fv(ball->a);
	glVertex3f(0, 0, 0);
	glVertex3fv(ball->v);
	glEnd();
	glPopMatrix();
}

void simulate_ball(void *data, state_t *state, float t, float dt)
{
	ball_t *ball = data;
	ball->a[0] =  - ball->x[0];
	ball->v[0] +=   ball->a[0] * dt;
	ball->x[0] +=   ball->v[0] * dt;
}

object_t *ball_new(float r)
{
	ball_t *ball   = calloc(sizeof(ball_t), 1);
	ball->r        = r;
	ball->simulate = simulate_ball;
	ball->draw     = ball_draw;
	ball->v[0] = 1.0;
	ball->scale[0] = 1.0; 
	ball->scale[1] = 1.0;
	ball->scale[2] = 1.0;
	return (object_t*)ball;
}

void ball_delete(object_t *ball)
{
	free(ball);	
}
