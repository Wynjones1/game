#pragma once
#include "drawable.h"

class Object : public Drawable
{
public:
	Object()
	: model_matrix(1.0)
	{}

	void Draw(Program &program)
	{}

	virtual void Simulate(float dt) = 0;

	glm::mat4 model_matrix;
};

void Draw(Object *d, Program &program);

class DynamicObject : public Object
{
public:
};

class StaticObject : public Object
{
public:
	void Simulate(float dt)
	{}
};