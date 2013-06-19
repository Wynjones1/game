#ifndef BALL_H
#define BALL_H
#include "object.h"

typedef struct
{
	OBJ_DEFS;
	float r;
}ball_t;

object_t *ball_new(float r);

#endif
