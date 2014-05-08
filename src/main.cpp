#include <iostream>
#include "events.h"
#include "window.h"
#include "shaders.h"
#include "drawable.h"
#include "input_state.h"
#include "player.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "config.h"
#include "texture.h"
#include "weapons.h"

int main(int argc, char **argv)
{
	/* Initialise the game */
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

	//Mesh *world    = new Mesh(program, "./data/test_world.ply");
	//world->texture = new Texture("./data/wall.ppm");
	//window.AddDrawable(world);

	Player *player = new Player();

	SDL_SetRelativeMouseMode(SDL_TRUE);

	/* Start the mainloop */
	float time = SDL_GetTicks() / 1000.0f;
	float new_time, frame_time;
	float accumulator = 0.0;
	float dt = 0.01f;
	while(1)
	{
		new_time   = SDL_GetTicks() / 1000.0f;
		frame_time = new_time - time;
		time       = new_time;

		accumulator += frame_time;

		while(accumulator >= dt)
		{
			player->Simulate(dt);
			if(g_input_state.space_key)
			{
				window.AddDrawable(new Bullet(program, player->pos, glm::vec3(-sinf(player->rot), 0, -cosf(player->rot))));
			}
			for(unsigned int i = 0; i < window.drawables.size();)
			{
				auto d = window.drawables[i];
				d->Simulate(dt);
				if(!d->alive)//Kill the object
				{
					window.drawables.erase(window.drawables.begin() + i);
				}
				else
				{
					i++;
				}
			}
			for(auto d : window.drawables)
			{
				d->Simulate(dt);
				if(!d->alive)
				{

				}
			}
			handler.HandleEvents();
			accumulator -= dt;
		}

		glUniformMatrix4fv(program.view, 1, GL_FALSE, glm::value_ptr(player->GetViewMatrix()));
		window.Render();
	}

	return 0;
}
