#include "bounds.h"
#include <algorithm>
#include <windows.h>
#include <GL/gl.h>
#include <math.h>

bounds_t::bounds_t(int min_in[2], int max_in[2])
{
	std::copy(min_in, min_in + 2, min);
	std::copy(max_in, max_in + 2, max);

	for(int i = 0; i < NUM_DIMENSIONS; i++)
	{
		center[i] = (min[i] + max[i]) / 2;
	}
	width  = center[0] - min[0];
	height = center[1] - min[1];
}

bounds_t::bounds_t(int x_min, int y_min, int x_max, int y_max)
{
	min[0] = x_min;
	min[1] = y_min;
	max[0] = x_max;
	max[1] = y_max;

	for(int i = 0; i < NUM_DIMENSIONS; i++)
	{
		center[i] = (min[i] + max[i]) / 2.0f;
	}
	width  = center[0] - min[0];
	height = center[1] - min[1];
}

bool bounds_t::overlaps(const bounds_t &bound) const
{
	/*	If any of the axis dont overlap	*
	*	then the bounds dont overlap	*/
	for(int i = 0;i < 2; i++)
	{
		if(!overlaps(bound, i))
		{
			return false;
		}
	}
	return true;
}

bool bounds_t::overlaps(const bounds_t &bound, int axis) const
{
	int a_width, b_width, total, abs_cent;
	a_width = center[axis] - min[axis];
	b_width = bound.center[axis] - bound.min[axis];
	total = a_width + b_width;
	abs_cent = fabs((float)(center[axis] - bound.center[axis]));
	return !(abs_cent > total);
}

void bounds_t::draw(void) const
{
#if DRAW_BOUNDS
	glPushMatrix();
	glLoadIdentity();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POINTS);
		glVertex2iv(center);
	glEnd();
	glBegin(GL_QUADS);
		glVertex2f(min[0], min[1]);
		glVertex2f(min[0], max[1]);
		glVertex2f(max[0], max[1]);
		glVertex2f(max[0], min[1]);
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPopMatrix();
#endif
}
