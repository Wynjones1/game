#ifndef SIMULATE_H
#define SIMULATE_H
#include "state.h"

struct object;

void simulate(state_t *state, float t, float dt);
void simulate_object(struct object *obj, state_t *state, float t, float dt);

#endif
