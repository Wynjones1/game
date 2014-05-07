#include "player.h"
#include "input_state.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#define INV_SQRT2 0.70710678118f

Player::Player()
: rot(0.0f)
, rot_speed(0.01f)
, speed(1.5f)
{}

void Player::Simulate(double dt)
{
	if(g_input_state.LetterPressed('w'))
	{
		MoveForward(dt);
	}
	if(g_input_state.LetterPressed('s'))
	{
		MoveBackward(dt);
	}
	if(g_input_state.LetterPressed('a'))
	{
		StrifeLeft(dt);
	}
	if(g_input_state.LetterPressed('d'))
	{
		StrifeRight(dt);
	}
	if(g_input_state.mouse_rot[0])
	{
		Turn();
	}
	Report();
}

void Player::Report(void)
{
	std::cout << "Pos      : " << pos.x << " " << pos.y << " " << pos.z  << std::endl;
	std::cout << "Rot      : " << rot       << std::endl;
	std::cout << "Rot Speed: " << rot_speed << std::endl;
	std::cout << "Speed    : " << speed     << std::endl;
	std::cout << std::endl;
}

void Player::Turn(void)
{
	rot += (float) g_input_state.mouse_rot[0] * rot_speed;
}

void Player::MoveForward(double dt)
{
	float step = 1.0;
	if(g_input_state.LetterPressed('a') != g_input_state.LetterPressed('d'))
	{
		step = INV_SQRT2;
	}
	glm::vec4 mov(0, 0, speed * dt * -step, 1);
	mov     = glm::rotate(glm::mat4(), rot, glm::vec3(0, 1, 0)) * mov;
	pos[0] += mov[0];
	pos[1] += mov[1];
	pos[2] += mov[2];
}

void Player::MoveBackward(double dt)
{
	float step = 1.0;
	if(g_input_state.LetterPressed('a') != g_input_state.LetterPressed('d'))
	{
		step = INV_SQRT2;
	}
	glm::vec4 mov(0, 0, speed * dt * step, 1);
	mov     = glm::rotate(glm::mat4(), rot, glm::vec3(0, 1, 0)) * mov;
	pos[0] += mov[0];
	pos[1] += mov[1];
	pos[2] += mov[2];
}

void Player::TurnLeft(double dt)
{
	rot += (float)(rot_speed * dt);
}

void Player::TurnRight(double dt)
{
	rot -= (float)(rot_speed * dt);
}

glm::mat4 Player::GetViewMatrix(void)
{
	//First rotate our view
	auto r = glm::rotate(glm::mat4(1.0), -rot, glm::vec3(0, 1, 0));
	//Now Translate to the pos.
	auto t = glm::translate(r, -pos);
	return t;
}

void Player::StrifeLeft(double dt)
{
	float step = 1.0;
	if(g_input_state.LetterPressed('w') != g_input_state.LetterPressed('s'))
	{
		step = INV_SQRT2;
	}
	glm::vec4 mov(speed * dt * -step, 0, 0, 1);
	mov     = glm::rotate(glm::mat4(), rot, glm::vec3(0, 1, 0)) * mov;
	pos[0] += mov[0];
	pos[1] += mov[1];
	pos[2] += mov[2];
}
void Player::StrifeRight(double dt)
{
	float step = 1.0;
	if(g_input_state.LetterPressed('w') != g_input_state.LetterPressed('s'))
	{
		step = INV_SQRT2;
	}
	glm::vec4 mov(speed * dt * step, 0, 0, 1);
	mov     = glm::rotate(glm::mat4(), rot, glm::vec3(0, 1, 0)) * mov;
	pos[0] += mov[0];
	pos[1] += mov[1];
	pos[2] += mov[2];
}
