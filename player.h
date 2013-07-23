#ifndef PLAYER_H
#define PLAYER_H
#include "object.h"
#include <algorithm>

class player_t : public object_t
{
public:
	player_t(void);
	virtual void   simulate(const state_t &state);
	virtual void   calculate_bounds(void);
	virtual void   draw();
	virtual std::string type(void);
private:
	int width;
	int height;
	float jump_time;
	bool standing;
};

#endif
