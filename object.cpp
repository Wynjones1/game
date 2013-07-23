#include "object.h"
#include <algorithm>
#include <GLFW/glfw3.h>

object_t::object_t(bool dynamic)
: dynamic(dynamic)
, recalculate_bounds(true)
, collision(collision_face_none)
{
	std::fill_n(x, 2, 0);
	std::fill_n(v, 2, 0);
	std::fill_n(a, 2, 0);
	std::fill_n(scale,  2, 1.0);
	std::fill_n(colour, 4, 1.0);
}

void object_t::transfer_to_last(void)
{
	std::copy_n(x, 2, last_x);
	std::copy_n(v, 2, last_v);
	std::copy_n(a, 2, last_a);
	last_bounds = bounds;
	last_collision = collision;
}

bool object_t::collides(object_t *obj)
{
	bounds_t temp = obj->get_bounds();
	return get_bounds().overlaps(temp);
}

collision_face_e object_t::collision_face(object_t *object)
{
	int out = collision_face_none;
	/*	Check each face, if it has collided between *
	*	last and now it is a collision face.		*
	*	the direction of the velocity decides if	*
	*	it is top/bottom or left/right				*/
	const bounds_t &obj_cur = object->get_bounds();
	const bounds_t &obj_last = object->last_bounds;
	for(int i = 0; i < 2; i++)
	{
		if(!last_bounds.overlaps(obj_last, i) &&
			bounds.overlaps(obj_cur, i))
		{
			if(v[i] > 0.0)
			{
				if(i == 0)
				{
					out |= collision_face_right;
				}
				else
				{
					out |= collision_face_top;
				}
			}
			else
			{
				if(i == 0)
				{
					out |= collision_face_left;
				}
				else
				{
					out |= collision_face_bottom;
				}
			}
		}
	}
	return (collision_face_e)out;
}

void object_t::set_scale(int s)
{
	std::fill_n(scale, 2, s);
}

void object_t::set_scale(int x_in, int y_in)
{
	scale[0] = x_in;
	scale[1] = y_in;
}

bool object_t::standing(const object_t &obj)
{
	return false;
}

void object_t::set_x(int *x_in)
{
	x[0] = x_in[0];
	x[1] = x_in[1];
}

void object_t::set_x(int x_in, int y_in)
{
	x[0] = x_in;
	x[1] = y_in;
}

void object_t::set_v(int *v_in)
{
	if(dynamic)
	{
		v[0] = v_in[0];
		v[1] = v_in[1];
	}
}
void object_t::set_v(int x_in, int y_in)
{
	if(dynamic)
	{
		v[0] = x_in;
		v[1] = y_in;
	}
}

void object_t::set_a(int *a_in)
{
	if(dynamic)
	{
		a[0] = a_in[0];
		a[1] = a_in[1];
	}
}

void object_t::set_a(int x_in, int y_in)
{
	if(dynamic)
	{
		a[0] = x_in;
		a[1] = y_in;
	}
}

/* Positions the object in the world. */
void object_t::pre_draw(void)
{
	glPushMatrix();
	glScalef(scale[0], scale[1], 1);
	glTranslatef(x[0], x[1], 0);
}

void object_t::post_draw(void)
{
	glPopMatrix();
}

void object_t::draw(void)
{
	bounds_t b  = get_bounds();
	int &width  = b.width;
	int &height = b.height;
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2i(-width, -height);
	glVertex2i(-width, height);
	glVertex2i(width, height);
	glVertex2i(width, -height);
	glEnd();
}

const bounds_t &object_t::get_bounds(void)
{
	if(recalculate_bounds)
	{
		calculate_bounds();
	}
	return bounds;
}

void object_t::pre_simulate(void)
{
	transfer_to_last();
}
