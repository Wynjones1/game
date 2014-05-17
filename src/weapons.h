#pragma once
#include "object.h"
#include "mesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

class Bullet : public DynamicObject
{
public:
	Bullet(glm::vec3 _pos, glm::vec3 _vel)
		: vel(_vel)
		, pos(_pos)
		, model_matrix(1.0)
	{
		//vel[0] += ((float)rand() / RAND_MAX) * 0.05f;
		//vel[1] += ((float)rand() / RAND_MAX) * 0.05f;
		//vel[2] += ((float)rand() / RAND_MAX) * 0.05f;
		life = 3.0f;

		pos    += glm::vec3(0.3f, 0.3, 0.3f) * glm::cross(vel, glm::vec3(0, 1, 0));
		pos[1] -= 0.3f;
		if(!mesh)
		{
			mesh = new Mesh("./data/sphere.ply");
			glBindVertexArray(mesh->vao);
			glDisableVertexAttribArray(1);
			glVertexAttrib3f(1, 1, 0, 0);
			glBindVertexArray(0);
		}
	}

	void Simulate(float dt)
	{
		pos += 40 * dt * vel;
		model_matrix = glm::translate(glm::mat4(1.0), pos);
		life -= dt;
		if(life <= 0.0)
		{
			alive = false;
		}
	}

	void Draw(Program &program)
	{
		glUniformMatrix4fv(program.model, 1, GL_FALSE, &model_matrix[0][0]);
		mesh->Draw(program);
	}

	glm::vec3 vel;
	glm::vec3 pos;
	float life;
private:
	static Mesh *mesh;
	glm::mat4 model_matrix;
};
