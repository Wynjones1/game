#include "draw.h"
#include "GL/gl.h"
#include <math.h>

void draw_obj(object_t *obj, state_t *state);

void draw(state_t *state)
{
	object_t **objects = list_data(state->objects);
	for(int i = 0;i < list_size(state->objects); i++)
	{
		draw_obj(objects[i], state);
	}
}

void draw_obj(object_t *object, state_t *state)
{
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(object->x[0], object->x[1], object->x[2]);
	glRotatef(180.0 / M_PI * object->rot[2], 0, 0, 1);
	glScalef(object->scale[0], object->scale[1], object->scale[2]);

	object->draw(object, state);

	glPopMatrix();
}
