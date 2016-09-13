#ifndef _CORE_TIME_H_
#define _CORE_TIME_H_

static double current_time;
static double previous_time;
static double frame_time;
static double target_time;

void init_time(double target_fps);
double get_time();
void begin_frame_time();
void end_frame_time();
float get_fps();

#endif
