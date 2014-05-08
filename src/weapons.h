#pragma once
#include "drawable.h"

class Bullet : public Mesh
{
public:
	Bullet(Program &program, glm::vec3 pos, glm::vec3 vel)
		: Mesh(program)
		, vel(vel)
		, life(10.0)
	{
		this->pos = pos;
	}

	void Simulate(float dt)
	{

		pos[0] += 50.0f * vel[0] * dt;
		pos[1] += 50.0f * vel[1] * dt;
		pos[2] += 50.0f * vel[2] * dt;
		life -= dt;
		//if(life < 0) alive = false;
		

	}

	void Draw()
	{
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		Mesh::Draw();
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glm::vec3 vel;
	float life;
};