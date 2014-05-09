#pragma once
#include "object.h"
#include "mesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

class Bullet : public DynamicObject
{
public:
	Bullet(glm::vec3 pos, glm::vec3 vel)
		: vel(vel)
		, pos(pos)
		, life(10.0)
		, model_matrix(1.0)
	{
		if(!mesh)
		{
			mesh = new Mesh();
		}
	}

	void Simulate(float dt)
	{
		pos += 5 * dt * vel;
		model_matrix = glm::translate(glm::mat4(1.0), pos);
		model_matrix = glm::scale(model_matrix, glm::vec3(0.5, 0.5, 0.5));
		life -= dt;
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