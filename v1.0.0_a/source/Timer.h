#pragma once

#include <SDL.h>
#include <iostream>

using namespace std;

class Timer {


private:

	const int fps = 59; // value that fps rate will be locked to
	int curr_time;// time atm
	int prev_time; // since when we started counting
	float elapsed_time; // time between previous and current time
	float frame_time; // time of a frame, =1 / fps
	void track(int comm);


public:

	Timer();
	~Timer();

	void start();
	void stop();
	float get_time(bool do_track);
	void restart();
	float get_frame_time(bool do_sec);


};

