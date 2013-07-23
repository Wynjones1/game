#ifndef BALL_H
#define BALL_H
#include "object.h"

class ball_t : public object_t
{
public:
	ball_t(void);
	ball_t(int radius);
	ball_t(int radius, float r, float g, float b, float a);
	ball_t(int radius, float r, float g, float b);
	void draw(void);
	void simulate(const state_t &s);
	void calculate_bounds(void);
private:
	int r;
};

#endif
