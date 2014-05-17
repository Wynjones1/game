#pragma once
#include "drawable.h"

class AABB : public Drawable
{
public:
	void Draw(Program &program);
	glm::vec3 min, max;
};