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
#include "object.h"

void Setup(void)
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
	glVertexAttrib4f(1, 0.0, 1.0, 0.0, 1.0);
	glVertexAttrib4f(2, 0.0, 0.0, 1.0, 1.0);
	glVertexAttrib2f(3, 0.0, 0.0);
}

int main(int argc, char **argv)
{
	/* Initialise the game */
	Window       window = Window(g_config.width, g_config.height);

	Setup();

	EventHandler handler;
	Program      program("./data/simple.vertex", "./data/simple.fragment");
	program.Use();

	glm::mat4 projection = glm::perspective(60.0f * (float)(180.0f / M_PI), g_config.aspect, 0.01f, 1000.0f);
	glUniformMatrix4fv(program.projection, 1, GL_FALSE, glm::value_ptr(projection)); 

	Mesh *world    = new Mesh("./data/test_world.ply");
	world->texture = new Texture("./data/wall.ppm");
	Axis axis;
	Player player = Player();

	SDL_SetRelativeMouseMode(SDL_TRUE);

	std::vector<Object*> objects;

	objects.push_back(world);

	/* Start the mainloop */
	float time = SDL_GetTicks() / 1000.0f;
	float new_time, frame_time;
	float accumulator = 0.0;
	float dt = 0.01f;
	Texture *tex0 = new Texture("./data/grid.ppm");
	//TODO This will need to be fixed.
	game_controller = SDL_GameControllerOpen(0);
	while(1)
	{
		new_time   = SDL_GetTicks() / 1000.0f;
		frame_time = new_time - time;
		time       = new_time;

		accumulator += frame_time;

		while(accumulator >= dt)
		{
			player.Simulate(dt);
			if(g_input_state.a)// && player.fire_recharge == 0.0)
			{
				Bullet *temp = new Bullet(player.pos, glm::vec3(-sinf(player.rot), 0, -cosf(player.rot)));
				player.fire_recharge = 0.5f;
				objects.push_back(temp);
			}
			for(unsigned int i = 0; i < objects.size(); i++)
			{
				Object *s = objects[i];
				s->Simulate(dt);
				if(!s->alive)
				{
					objects.at(i) = objects.at(objects.size() - 1);
					objects.pop_back();
					i--;
				}
			}

			handler.HandleEvents();
			accumulator -= dt;
		}
		program.Use();
		glUniformMatrix4fv(program.view, 1, GL_FALSE, glm::value_ptr(player.GetViewMatrix()));
		//Draw each of the objects.
		for(auto d : objects)
		{
			Draw(d, program);
		}
		axis.Draw(program);
		player.Draw(program);
		window.SwapBuffer();
	}

	return 0;
}
