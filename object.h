#ifndef OBJECTS_H
#define OBJECTS_H
#include "state.h"

typedef void (*simulate_fn)(void *object, state_t *state, float t, float dt);
typedef void (*draw_fn)(void *object, state_t *state);
typedef void (*delete_fn)(void *object, state_t *state);

#define OBJ_DEFS\
	float            life;\
	float            x[3];\
	float            v[3];\
	float            a[3];\
	float            rot[3];\
	float            scale[3];\
	simulate_fn      simulate;\
	draw_fn          draw;\
	delete_fn        delete\

typedef struct object
{
	OBJ_DEFS;
}object_t;

#endif
