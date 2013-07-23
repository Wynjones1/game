#ifndef OBJECT_H
#define OBJECT_H
#include "drawable.h"
#include "bounds.h"
#include <string>

class state_t;

enum collision_face_e
{
	collision_face_none   = 0x0,
	collision_face_top    = 0x1,
	collision_face_bottom = 0x2,
	collision_face_left   = 0x4,
	collision_face_right  = 0x8
};

class object_t : public drawable
{
public:
	object_t(bool dynamic = true);

	void set_scale(int s);
	void set_scale(int x_in, int y_in);

	void set_x(int *x);
	void set_x(int x_in, int y_in);

	void set_v(int *v);
	void set_v(int x_in, int y_in);

	void set_a(int *a);
	void set_a(int x_in, int y_in);

	virtual void             simulate(const state_t &s) = 0;
	virtual bool             collides(object_t *object);
	virtual const bounds_t  &get_bounds(void);
	virtual void             calculate_bounds(void) = 0;
	collision_face_e         collision_face(object_t *object);

	void transfer_to_last(void);

	void pre_draw(void);
	void pre_simulate(void);
	void post_draw(void);
	void draw(void);

	bool standing(const object_t &obj);

	virtual std::string type() = 0;

	float  x[2];
	float  v[2];
	float  a[2];
	bounds_t bounds;
	collision_face_e collision;

	float  last_x[2];
	float  last_v[2];
	float  last_a[2];
	bounds_t last_bounds;
	collision_face_e last_collision;

	int   scale[2];
	float colour[4];
	bool  dynamic;
	bool  recalculate_bounds;
};

#endif
