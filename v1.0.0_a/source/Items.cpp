#include "stdafx.h"
#include "Items.h"





Items::Items(Background *bg, const string &texture_path, int width, int height, int x, int y, int select_button, int x_offset, int y_offset):
	BG(bg), w(width), h(height), x(x), y(y), x_offset(x_offset), y_offset(y_offset), select_function(select_button){
}


void Items::drag() {




}void Items::sprite_manager() {


	check_pos();


	switch (key) {


	case 1:
		if (is_in) {

			tex_selector.x = x_offset;
			tex_selector.y = y_offset;
			cout << "ljeft and in " << endl;
			button.x = mouse_x;
		}
		break;

	case 2:

		if (is_in) {

			tex_selector.x = 0;
			tex_selector.y = y_offset;
			cout << "rajt and in" << endl;
		}
		break;

	}

	key = 0;
}


void Items::draw() {

	button = { x - BG->get_camera_x() ,y,w,h };



	SDL_RenderCopy(Window::renderer, button_texture, &tex_selector, &button);

}