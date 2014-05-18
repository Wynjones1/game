#include "player.h"
#include "input_state.h"
#include "events.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <algorithm>
#define INV_SQRT2 0.70710678118f

Player::Player()
: rot(0.0f)
, rot_speed(0.01f)
, speed(5.0f)
, fire_recharge(0.0f)
, recharge_rate(1.0f)
{}

void Player::Keyboard(float dt)
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
}

void Player::Controller(float dt)
{
	if(g_input_state.laxis[0] < -0.3)
	{
		StrifeLeft(-g_input_state.laxis[0] * dt);
	}
	else if(g_input_state.laxis[0] > 0.3)
	{
		StrifeRight(g_input_state.laxis[0] * dt);
	}

	if(g_input_state.laxis[1] < -0.3)
	{
		MoveForward(-g_input_state.laxis[1] * dt);
	}
	else if(g_input_state.laxis[1] > 0.3)
	{
		MoveBackward(g_input_state.laxis[1] * dt);
	}

	if(g_input_state.raxis[0] < -0.3 || g_input_state.raxis[0] > 0.3)
	{
		rot -= 3.5 * g_input_state.raxis[0] * rot_speed;
	}
}

void Player::Simulate(float dt)
{
	if(g_game_controller)
	{
		Controller(dt);
	}
	else
	{
		Keyboard(dt);
	}
	fire_recharge = std::max(0.0f, fire_recharge - recharge_rate * dt);
	//Report();
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

void Player::Draw(Program &program)
{
	glm::mat4 m(1.0);
	m = glm::translate(m, pos);
	m = glm::rotate(m, rot, glm::vec3(0, 1, 0));
	m = glm::translate(m, glm::vec3(0.6, -0.5, -1));
	m = glm::scale(m, glm::vec3(2.0));
	glDisable(GL_DEPTH_TEST);
	glUniformMatrix4fv(program.model, 1, GL_FALSE, &m[0][0]);
	glEnable(GL_DEPTH_TEST);
}
