#ifndef PLATFORM_H
#define PLATFORM_H
#include "object.h"

class platform_t : public object_t
{
public:
	platform_t(int width, int height);
	void 			calculate_bounds(void);
	void            draw(void);
	void            simulate(const state_t &s);
	std::string     type(void);
private:
	int width, height;
};
#endif
