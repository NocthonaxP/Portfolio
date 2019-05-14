#include "stdafx.h"
#include "Button.h"

Button::Button(Background *bg, const string &texture_path, int width, int height, int x, int y, int select_button, int x_offset, int y_offset):
  BG(bg),w(width), h(height), x(x), y(y), x_offset(x_offset), y_offset(y_offset), select_function(select_button){

	
	select_function = select_button;


	button_surface = IMG_Load(texture_path.c_str());

	tex_selector = { 0,0, x_offset, y_offset };

	if (button_surface == NULL) {
		cout << "Failed loading the button texture" << endl;
	}

	button_texture = SDL_CreateTextureFromSurface(Window::renderer, button_surface);

	if (button_texture == NULL) {

		cout << "Failed to create the texture" << endl;
	}
	
}


void Button::draw() {

	button = { x- BG->get_camera_x() ,y,w,h};



		SDL_RenderCopy(Window::renderer, button_texture, &tex_selector, &button);
	
}



void Button::check_pos() {

	//hower else idle
	if (mouse_x > x - BG->get_camera_x() && mouse_x < x+w - BG->get_camera_x() && mouse_y>y && mouse_y < y+h) {
		is_in = true;
		tex_selector.x = x_offset;
		tex_selector.y = 0;
	}
	else {
		is_in = false;
		tex_selector.x = 0;
		tex_selector.y = 0;
	}

	
}

void Button::sprite_manager() {

	
	check_pos();

	
	switch (key) {


	case 1:
		is_pressed_r = 0;
		is_pressed_l = 0;

		if (is_in) {

			tex_selector.x = x_offset;
			tex_selector.y = y_offset;
			cout << "ljeft and in " << endl;
			is_pressed_r = 0;
			is_pressed_l = 1;
		}
		break;

	case 2:

		if (is_in) {
			
			tex_selector.x = 0;
			tex_selector.y = y_offset;
			cout << "rajt and in" << endl;
			is_pressed_r = 1; 
			is_pressed_l = 0; 
		}
		break;

	}

	key = 0;

}
 
void Button::destroy() {

	SDL_DestroyTexture(button_texture);
	SDL_FreeSurface(button_surface);
}