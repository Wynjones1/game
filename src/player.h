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
	float     fire_recharge;
	float     recharge_rate;

	void      Simulate(float dt = 1.0 / 60.0);
	void      Report(void);
	void      MoveForward(double dt);
	void      MoveBackward(double dt);
	void      TurnLeft(double dt);
	void      TurnRight(double dt);
	void      Turn(void);
	void      StrifeLeft(double dt);
	void      StrifeRight(double dt);
	glm::mat4 GetViewMatrix(void);
};
