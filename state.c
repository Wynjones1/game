#include "state.h"
#include <string.h>
#include "object.h"

void state_init(state_t *state)
{
	state->objects = list(object_t *);
}

void state_add_object(state_t *state, void *object)
{
	list_push_back(state->objects, &object);	
}

