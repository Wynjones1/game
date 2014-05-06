#include "player.h"
#include "input_state.h"
#include <glm/gtc/matrix_transform.hpp>

Player::Player()
: rot(0.0f)
, rot_speed(1.0f)
, speed(0.1f)
{

}
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
		//TurnLeft(dt);
		StrifeLeft(dt);
	}
	if(g_input_state.LetterPressed('d'))
	{
		//TurnRight(dt);
		StrifeRight(dt);
	}
	if(g_input_state.mouse_rot[0])
	{
		Turn();
	}
}

void Player::Turn(void)
{
	rot += (float) g_input_state.mouse_rot[0] * 0.1f;
}

void Player::MoveForward(double dt)
{
	glm::vec4 mov(0, 0, speed * dt * -1, 1);
	mov     = glm::rotate(glm::mat4(), rot, glm::vec3(0, 1, 0)) * mov;
	pos[0] += mov[0];
	pos[1] += mov[1];
	pos[2] += mov[2];
}

void Player::MoveBackward(double dt)
{
	glm::vec4 mov(0, 0, speed * dt * 1, 1);
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
	glm::vec4 mov(speed * dt * -1, 0, 0, 1);
	mov     = glm::rotate(glm::mat4(), rot, glm::vec3(0, 1, 0)) * mov;
	pos[0] += mov[0];
	pos[1] += mov[1];
	pos[2] += mov[2];
}
void Player::StrifeRight(double dt)
{
	glm::vec4 mov(speed * dt * 1, 0, 0, 1);
	mov     = glm::rotate(glm::mat4(), rot, glm::vec3(0, 1, 0)) * mov;
	pos[0] += mov[0];
	pos[1] += mov[1];
	pos[2] += mov[2];
}