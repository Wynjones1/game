#include "simulate.h"
#include <math.h>
#include <string.h>
#include "object.h"

void simulate(state_t *state, float t, float dt)
{
	object_t **objects = list_data(state->objects);
	for(int i = 0;i < list_size(state->objects); i++)
	{
		objects[0]->simulate(objects[0], state, t, dt);
	}
}
