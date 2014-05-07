#include <iostream>
#include "events.h"
#include "window.h"
#include "shaders.h"
#include "drawable.h"
#include "defines.h"
#include "input_state.h"
#include "player.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "config.h"
#include "texture.h"

#define RED 255, 0, 0
#define GREEN 0, 255, 0
#define BLUE 0, 0, 255
#define WHITE 255, 255, 255
#define BLACK 0, 0, 0

int main(int argc, char **argv)
{
	Window       window = Window(g_config.width, g_config.height);

	EventHandler handler;
	Program      program;
	Shader       vertex_shader   = Shader(GL_VERTEX_SHADER,   "./data/simple.vertex");
	Shader       fragment_shader = Shader(GL_FRAGMENT_SHADER, "./data/simple.fragment");

	program.AddShader(vertex_shader);
	program.AddShader(fragment_shader);
	program.Compile();
	program.Use();

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
	glVertexAttrib4f(1, 0.0, 1.0, 0.0, 1.0);
	glVertexAttrib4f(2, 0.0, 0.0, 1.0, 1.0);
	glVertexAttrib2f(3, 0.0, 0.0);

	glm::mat4 projection = glm::perspective(60.0f * (float)(180.0f / M_PI), g_config.aspect, 0.01f, 1000.0f);
	glUniformMatrix4fv(program.projection, 1, GL_FALSE, glm::value_ptr(projection)); 

	Mesh *world    = new Mesh(program, "./data/test_world.ply");
	//Mesh *world    = new Mesh(program);
	world->texture = new Texture("./data/wall.ppm");

	Player *player = new Player();
	window.AddDrawable(world);

	SDL_SetRelativeMouseMode(SDL_TRUE);

	while(1)
	{
		player->Simulate();
		glUniformMatrix4fv(program.view, 1, GL_FALSE, glm::value_ptr(player->GetViewMatrix()));
		window.Render();
		handler.HandleEvents();
	}

	return 0;
}
