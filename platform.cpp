#include "platform.h"
#include <GL/gl.h>

platform_t::platform_t(int width, int height)
: width(width)
, height(height)
{}

void platform_t::calculate_bounds(void)
{
	bounds = bounds_t(x[0],x[1],x[0] + width,x[1] + height);
}

void platform_t::draw(void)
{
	glBegin(GL_QUADS);
	glColor4fv(colour);
	glVertex2i(0, 0);
	glVertex2i(0, height);
	glVertex2i(width, height);
	glVertex2i(width, 0);
	glEnd();
}

void platform_t::simulate(const state_t &s)
{}

std::string platform_t::type(void)
{
	return std::string("platform");
}
