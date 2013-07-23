#ifndef BOUNDS_H
#define BOUNDS_H
#include <iostream>

const int NUM_DIMENSIONS = 2;

class bounds_t
{
public:
	bounds_t(){};
	bounds_t(int min[2], int max[2]);
	bounds_t(int x_min, int y_min, int x_max, int y_max);

    bool overlaps(const bounds_t &bound) const;
    bool overlaps(const bounds_t &bound, int axis) const;
	void draw(void) const;
	friend std::ostream& operator<<(std::ostream &os, const bounds_t &bound)
	{
		os << "(" << bound.min[0] << "," << bound.min[1] << ")";
		os << " ";
		os << "(" << bound.max[0] << "," << bound.max[1] << ")";
		return os;
	}

	int min[2];
	int max[2];
	int   width, height;
	int center[2];
};

#endif
