#pragma once

#include "window.h"
#include <SDL_image.h>

class Background {


private:


	Window *Win;

	SDL_Rect camera;
	SDL_Rect rect_left;
	SDL_Rect rect_right;


	SDL_Surface *sur_world;
	SDL_Surface *sur_background;
	SDL_Surface *sur_picture;
							

	SDL_Texture *tex_world;

	int camera_beginning;
	int camera_mid;
	int camera_end;
	int speed;
	
	bool init(bool want_frame);


public:

	Background(Window *Win, int player_speedo, bool want_frame);

	int get_rect_left_x() { return rect_left.x; }
	int get_rect_right_x() { return rect_right.x; }
	int get_rect_left_w() { return rect_left.w; }
	int get_rect_right_w() { return rect_right.w; }
	int get_camera_x() { return camera.x; }
	int get_camera_w() { return camera.w; }
	int get_camera_h() { return camera.h; }
	void move_camera(int offset);
	
	void set_camera_size();
	void set_limiters_size();

	void draw();
	void scroll_lock();
	void destroy();
	bool camera_move_free;

};


