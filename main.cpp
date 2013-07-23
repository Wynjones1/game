#include <iostream>
#include <vector>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <stdlib.h>
#include "ball.h"
#include "drawable.h"
#include "state.h"
#include "platform.h"
#include "player.h"

int irand(int min = 0.0, int max = 1.0)
{
	int out;
	int range = max - min;
	out = rand();
	out = range * (out / RAND_MAX) + min;
	return out;
}

int main(void)
{
	state_t &main_state = *state_t::get_state();
#if 1
	//srand(time(0));

	object_t *obj;

	obj = new player_t();
	obj->set_x(100, 400);
	main_state.add(obj);
	std::cout << obj->x[0] << "," << obj->x[1] << std::endl;

	//Floors
	obj = new platform_t(30, 1000);
	obj->set_x(-30, 0);
	main_state.add(obj);

	obj = new platform_t(30, 1000);
	obj->set_x(main_state.width - 1, 0);
	main_state.add(obj);

	obj = new platform_t(1600, 30);
	obj->set_x(0, -30);
	main_state.add(obj);

	obj = new platform_t(1600, 30);
	obj->set_x(0, main_state.height - 1);
	main_state.add(obj);

#if 1
	obj = new platform_t(50, 1000);
	obj->set_x(400,0);
	main_state.add(obj);

	obj = new platform_t(1600, 50);
	obj->set_x(0,200);
	main_state.add(obj);
#endif
#if 0
	//other platforms
	obj = new platform_t(200, 100);
	obj->set_x(600,100);
	main_state.add(obj);

	obj = new platform_t(200, 100);
	obj->set_x(600,500);
	main_state.add(obj);

	obj = new platform_t(200, 100);
	obj->set_x(600,500);
	main_state.add(obj);

	obj = new platform_t(200, 1000);
	obj->set_x(1000,0);
	main_state.add(obj);
#endif
#endif

	float current_time = state_t::get_time();
	float accumulator  = 0;
	float t = 0, new_time, frame_time;

	while(!main_state.is_done())
	{
		main_state.process_events();

		new_time   = state_t::get_time();

		frame_time = new_time - current_time;
		if(frame_time > 0.25)
			frame_time = 0.25;

		current_time = new_time;
		accumulator += frame_time;

		int tick = 0;
		while(accumulator >= main_state.dt)
		{
			t += main_state.dt;
			accumulator -= main_state.dt;
			main_state.simulate();
		}
		main_state.render();
	}
	glfwTerminate();
	return 0;
}
