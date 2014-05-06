#pragma once
#include "drawable.h"

class AABB : public Drawable
{
public:
	void Draw();
	glm::vec3 min, max;
};