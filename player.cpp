#include "player.h"
#include "state.h"

player_t::player_t(void)
: width(100)
, height(200)
, jump_time(0.0)
, standing(false)
{
	a[1] = -900;
}

std::string player_t::type(void)
{
	return std::string("player");
}


void player_t::simulate(const state_t &state)
{
	const std::vector<object_t*> &objs = state.objects;
	collision_face_e face = collision_face_none;
	//Store the previous state.
	transfer_to_last();
	bool collided = false;

	if(state.SPACE && standing)
	{
		v[1] = 650;	
		a[1] = state.gravity[1];
	}

	if(state.letters['A' - 'A'] && ! state.letters['D' - 'A'])
	{
		v[0] = -300;	
	}
	else if(state.letters['D' - 'A'])
	{
		v[0] = 300;	
	}
	else
	{
		v[0] = 0;
	}

	for(int i = 0;i < 2; i++)
	{
		v[i] += a[i] * state.dt;
		x[i] += v[i] * state.dt;
	}
	//Check for all collisions
	standing = false;
	for(int i = 0;i < objs.size(); i++)
	{
		object_t *t = objs[i];
		if(t != this && collides(t))
		{
		#if 1
				collision_face_e temp;
				temp = collision_face(t);
				if(temp == collision_face_bottom)
				{
					standing = true;
				}
				face = (collision_face_e)(face | temp);
		#endif
			collided = true;
		}
	}
	if(collided)
	{
		if(face == collision_face_none)
			face = last_collision;
		if(face & collision_face_left)
		{
			std::cout << "left ";
			v[0] = 0.0;
			x[0] = last_x[0];
		}
		if(face & collision_face_right)
		{
			std::cout << "right ";
			v[0] = 0.0;
			x[0] = last_x[0];
		}
		if(face & collision_face_top)
		{
			std::cout << "top ";
			v[1] = -last_v[1];
		}
		if(face & collision_face_bottom)
		{
			std::cout << "bottom ";
			v[1] = 0.0;
			x[1] = last_x[1];
			a[1] = 0.0;
		}
		std::cout << std::endl;
		collision = face;
	}
	else
	{
		standing = false;
		a[1] = state.gravity[1];
	}

}

void player_t::calculate_bounds(void)
{
	bounds = bounds_t(x[0] - width / 2, x[1] - height / 2, x[0] + width / 2, x[1] + height / 2);
}

void player_t::draw()
{
	int wh = width  / 2;
	int hh = height / 2;
	glBegin(GL_QUADS);
	glColor4fv(colour);
	glVertex2i(-wh,-hh);
	glVertex2i(-wh, hh);
	glVertex2i( wh, hh);
	glVertex2i( wh,-hh);
	glEnd();
}
