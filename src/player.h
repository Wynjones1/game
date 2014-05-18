#pragma once
#include "object.h"
#include "mesh.h"

class Player : DynamicObject
{
public:
	Player();

	glm::vec3 pos;
	float     rot;
	float     rot_speed;
	float     speed;
	float     fire_recharge;
	float     recharge_rate;

	void      Simulate(float dt);
	void      Report(void);
	void      MoveForward(double dt);
	void      MoveBackward(double dt);
	void      TurnLeft(double dt);
	void      TurnRight(double dt);
	void      Turn(void);
	void      StrifeLeft(double dt);
	void      StrifeRight(double dt);
	glm::mat4 GetViewMatrix(void);

	void Draw(Program &program);

	void Keyboard(float dt);
	void Controller(float dt);
};
