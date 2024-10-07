#include "utilities.h"				// self written utilities
#include <iostream>
#include <ctime>
#include <cmath>
#include "../../libs/imgui/backends/imgui_impl_glfw.h"
#include <GLFW/glfw3.h>  // opengl i daha rahat kullanabilmek icin fonksion kutuphanesi


void blackboard()
{
    glfwInit();
    // Example hex color code
    float max = 0.0f;
    int prev_mod = -1;

	float time = glfwGetTime();
	float tant				= 0.0f;
	float animation_stage	= 1.0f;
	float waiting_delay		= 2.0f;
	float time_difference	= 0.0f;
	float time_pin			= time;
	float time_pin2			= time;


    while (1)
    {
		if (animation_stage == 1)
		{
			tant = 0.0f;
			if (time > time_pin + waiting_delay)
			{
				time_difference = time - time_pin;
				animation_stage += 1;
			}
		}
		else if (animation_stage == 2)
		{
			tant = abs(tan(time - time_difference));

			if (tant > 6.0f)
			{
				tant = 2000.0f;
				time_pin = time;
				animation_stage += 1;
			}
		}
		else if (animation_stage == 3)
		{
			tant = 2000.0f;
			if (time > time_pin + waiting_delay)
			{
				time_difference = time - time_pin;
				animation_stage += 1;
			}
		}
		else if (animation_stage == 4)
		{
			tant = abs(tan(time));

			if (tant < 0.05f)
			{
				tant = 0.0f;
				time_pin = time;
				animation_stage = 1;
			}
		}


		time = glfwGetTime();
        
		if (time > time_pin2 + .2f)
		{
			time_pin2 = time;
			std::cout << tant << " - " << time << std::endl;
		}
    }


}