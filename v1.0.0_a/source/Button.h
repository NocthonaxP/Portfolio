#pragma once

#include "Window.h"
#include "Background.h"


class Button {


private:	
	SDL_Rect button;
	SDL_Rect tex_selector;
	SDL_Surface *button_surface;
	SDL_Texture *button_texture;

	int key;
	int mouse_x;
	int mouse_y;
	int x_offset;
	int y_offset;

	int w, h, x, y;

	bool is_in;
	
	Background *BG;

	
	void check_pos();

	bool is_pressed_l = 0;
	bool is_pressed_r = 0; 

public:

	Button(Background *bg,  const string &texture_path, int width, int height, int x, int y, int select_button, int x_offset, int y_offset);

	int get_width() { return button.w; }
	int get_height() { return button.h; }
	int get_x() { return button.x; }
	int get_y() { return button.y; }
	int select_function;
	void set_key(int key) { this->key = key; }
	void set_mouse_pos(int x, int y) { mouse_x = x; mouse_y = y; }
	void destroy();
	void draw();
	void sprite_manager();
	bool get_is_pressed_r() { return is_pressed_l; };
	bool get_is_pressed_l() { return is_pressed_r; };
};



