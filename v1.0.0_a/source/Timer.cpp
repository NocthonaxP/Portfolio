#include "stdafx.h"
#include "Timer.h"

Timer::Timer() {

}

Timer::~Timer() {

}

void Timer::start() {
	restart();
	curr_time = SDL_GetTicks();
}

void Timer::stop() {

	prev_time = curr_time;

	curr_time = SDL_GetTicks();

	elapsed_time = (float)(curr_time - prev_time);
	
}

float Timer::get_time(bool do_track) {
	if (do_track) {
		track(3);
	}
	return elapsed_time;
}

void Timer::restart() {

	prev_time = NULL;
	elapsed_time = NULL;
	curr_time = NULL;
}

float Timer::get_frame_time(bool do_sec) {
	// bool sec- show time in seconds 

	frame_time = (float)(1000 / fps);

	if (do_sec) {

		return frame_time * 1000.0f;
	}
	else {

		return (float)frame_time;
	}
}

void Timer::track(int comm) {
	/*
	* comm:	    1- only FPS
	* 			2- elapsed time (ms) and FPS
	*			3- all times(ms) and FPS
	*			4- only FPS
	*			5- elapsed time(s) and FPS
	*			6- all times(s) and FPS
	*/

	switch (comm) {

	case 3:
		cout << "~~~~oOo Current time oOo~~~~" << endl << "\t" << curr_time << endl;
		cout << "~~~~oOo Previous time oOo~~~~" << endl << "\t" << prev_time << endl;


	case 2:
		cout << "~~~~oOo Elapsed time oOo~~~~" << endl << "\t" << elapsed_time << endl;


	case 1:
		cout << "~~~~oOo FPS oOo~~~~" << endl << "\t (desird/real)" << endl << "\t(" << fps << "," << 1 / (elapsed_time / 1000.0f) << ")" << endl << endl;
		break;

	case 6:
		cout << "~~~~oOo Current time oOo~~~~" << endl << "\t" << curr_time / 1000.0f << endl;
		cout << "~~~~oOo Previous time oOo~~~~" << endl << "\t" << prev_time / 1000.0f << endl;

	case 5:
		cout << "~~~~oOo Elapsed time oOo~~~~" << endl << "\t" << elapsed_time / 1000.0f << endl;

	case 4:
		cout << "~~~~oOo FPS oOo~~~~" << endl << "\t (desird/real)" << endl << "\t(" << fps << "," << 1 / (elapsed_time / 1000.0f) << ")" << endl << endl;
		break;


	}
}