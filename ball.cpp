#include "ball.h"
#include <algorithm>
#include "state.h"
#include <math.h>
#include <string.h>

ball_t::ball_t(void)
: r(5)
{
	std::fill_n(colour, 4, 1.0f);
}
ball_t::ball_t(int radius)
: r(radius)
{}

ball_t::ball_t(int radius, float r, float g, float b, float a)
{
	this->r = radius;
	colour[0] = r;
	colour[1] = g;
	colour[2] = b;
	colour[3] = a;
}

ball_t::ball_t(int radius, float r, float g, float b)
{
	this->r = radius;
	colour[0] = r;
	colour[1] = g;
	colour[2] = b;
	colour[3] = 1.0;
}

void ball_t::calculate_bounds(void)
{
	bounds = bounds_t(x[0] - r, x[1] - r, x[0] + r, x[1] + r);
}

void ball_t::simulate(const state_t &s)
{
	const std::vector<object_t*> &objs = s.objects;
	bool collided = false;
	int old_x[2];
	memcpy(old_x, x, sizeof(old_x));
	for(int i = 0;i < 2; i++)
	{
		v[i] += a[i] * s.dt;
		x[i] += v[i] * s.dt;
	}
	for(int i = 0;i < objs.size(); i++)
	{
		object_t *t = objs[i];
		if(t != this && collides(t))
			collided = true;
	}
	if(collided)
	{
			colour[0] = 1.0;
			colour[1] = 0.0;
			colour[2] = 0.0;
			colour[3] = 1.0;
			for(int i = 0; i < 2; i++)
			{
					v[i] = - v[i];
			}
			memcpy(x, old_x, sizeof(old_x));
	}
	else
	{
			colour[0] = 1.0;
			colour[1] = 1.0;
			colour[2] = 1.0;
			colour[3] = 1.0;
	}
}

void temp(float angle, int *x, int *y)
{
	*x = cosf(angle);
	*y = sinf(angle);
}

void ball_t::draw(void)
{
	float dx = 0.1f;
	glBegin(GL_TRIANGLE_FAN);
		glColor4fv(colour);
		glVertex2f(0.0, 0.0);
		for(float i = 0.0; i <= (2 * 3.1415926) + dx; i += dx)
		{
			int x, y;
			temp(i, &x, &y);
			glVertex2f(r * x, r * y);
		}
	glEnd();

	glColor4fv(colour);
	get_bounds().draw();
}
