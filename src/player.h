#pragma once
#include "drawable.h"

class Player
{
public:
	Player();

	glm::vec3 pos;
	float     rot;
	float     rot_speed;
	float     speed;

	void      Simulate(double dt = 1.0 / 60.0);
	void      MoveForward(double dt);
	void      MoveBackward(double dt);
	void      TurnLeft(double dt);
	void      TurnRight(double dt);
	void      Turn(void);
	void      StrifeLeft(double dt);
	void      StrifeRight(double dt);
	glm::mat4 GetViewMatrix(void);
};
