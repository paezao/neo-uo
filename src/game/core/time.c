#include "time.h"
#include <GLFW/glfw3.h>

void init_time(double target_fps)
{
    target_time = 1 / target_fps;
    previous_time = get_time();
}

double get_time()
{
    return glfwGetTime();
}

void begin_frame_time()
{
    current_time = get_time();
    previous_time = current_time;
}

void end_frame_time()
{
   current_time = get_time();
   frame_time = current_time - previous_time;
   previous_time = current_time;

   double extra_time = 0.0;
   while(frame_time < target_time)
   {
       current_time = get_time();
       extra_time = current_time - previous_time;
       previous_time = current_time;
       frame_time += extra_time;
   }
}

float get_fps()
{
    return (float)(1.0 / frame_time);
}
