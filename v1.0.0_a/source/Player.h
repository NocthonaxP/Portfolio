#pragma once

#include "window.h"
#include "Background.h"
#include <SDL_image.h>
#include "Timer.h"

// Player.h
class Player {


private:

	SDL_Rect rectangle;
	const int speed = 10;
	int wpn_selector = 0;
	bool is_played = 1;
	int m_w, m_h;
	int m_x, m_y;

	Window *Win;

	Background *BG;

	//animation stuff

	SDL_Rect sprite_Selector;
	SDL_Surface *sprite_sheet;
	SDL_Texture *sprite_tex;

	int sprite_counter = 0;
	const int max_sprite_count = 18;


public:
	Player(int w, int h, int x, int y, Window *obj_window);

	void destroy();
	void set_Up();// 1 for sharkie, 0 for animation 
	void draw();

	void mov_edge();

	void set_pos_x(int x) { m_x = x; }
	void set_pos_y(int y) { m_y = y; }
	void set_wpn_selector(int wpn_num) { wpn_selector = wpn_num; }
	void set_active(bool active) { is_played = active; }

	int  get_pos_x() { return m_x; }
	int  get_pos_y() { return m_y; }
	int  get_width() { return m_w; }
	int  get_height() { return m_h; }
	int  get_speed() { return speed; }
	int  get_wpn_selector() { return wpn_selector; }
	int get_Wcoordinates() { return m_x + BG->get_camera_x(); }
	bool get_active() { return is_played; }


	bool player_move_free = true;

	bool was_right = false;
	bool was_left = false;
	bool was_mid = false;
	bool walked_right = false;
	bool walked_left = false;
	int last_state = 0; // 1 r 2 l

	void sprite_manager();
	int direction;
};


