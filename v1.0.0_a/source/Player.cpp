#include "stdafx.h"
#include "player.h"

using namespace std;

// Player.cpp

Player::Player(int w, int h, int x, int y, Window *window) : 
	m_w(w), m_h(h), m_x(x), m_y(y), Win(window) {
	

	set_Up();
}

void Player::set_Up() {  //need to pass in a window reference, the Window doesnt have any default constructors because it's inheriting from the "Window", you need to actually initalize it

	IMG_Init(IMG_INIT_PNG);

	sprite_sheet =IMG_Load("res/char_spread2.png");

	sprite_tex = SDL_CreateTextureFromSurface(Window::renderer, sprite_sheet);
	sprite_Selector = { 0, 0, sprite_sheet->w / max_sprite_count, 60 };

}

void Player::draw() {

	rectangle = { m_x, m_y, m_w, m_h };
	
	SDL_RenderCopy(Window::renderer, sprite_tex, &sprite_Selector, &rectangle);

}

void Player::mov_edge() {

	if (m_x == 0) {
		m_x += speed;
		cout << "End of the screen, far left, width " << endl;
	}

	else if (m_x >= 1550 ) {
		m_x -= speed;
		cout << "End of the screen, far right, width " << endl;
	}
	else if (m_y == 600 - rectangle.h) {
		m_y += speed;
		cout << "End of the screen ,far up,  height " << endl;
	}

	else if (m_y >= 744 - rectangle.w) {
		m_y -= speed;
		cout << "End of the screen ,far bottom, height " << endl;
	}

}

void Player::sprite_manager() {


	sprite_Selector = { 0, 0, sprite_sheet->w / max_sprite_count, 55 };
	switch (direction) {


	case 0:


		if (walked_right) {
			sprite_Selector.y = 0;
			sprite_counter = 0;
		}
		if (walked_left) {
			sprite_Selector.y = sprite_Selector.h;
			sprite_counter = 0;
		}

		walked_left = false;
		walked_right = false;
		

		break;
	case 1: //right


		sprite_Selector.y = 0;
		if (!was_right) {
			sprite_Selector.x = sprite_sheet->w / max_sprite_count;
		}

		if (sprite_counter < max_sprite_count - 1) {
			sprite_counter += 1;

		}
		else {
			sprite_counter = 1;

		}

		walked_right = true;
		walked_left = false;
		last_state = 1; 
		break;

	case 2: //left


		sprite_Selector.y = sprite_Selector.h;
		if (walked_right) {
			sprite_Selector.x = sprite_Selector.w;
		}

		if (sprite_counter < max_sprite_count - 1) {
			sprite_counter += 1;
		}
		else {
			sprite_counter = 1;
		}

		walked_left = true;
		walked_right = false;
		last_state = 2; 
		break;

	}
	sprite_Selector.x = sprite_counter * sprite_Selector.w;


	if (direction == 3) {

		if (last_state==1) {

			sprite_Selector = { 0, 120, 130, 55 };
			 
		}
		if(last_state ==2) {

			sprite_Selector = { 130, 120, 130, 55 };

		}
	}

}

void Player::destroy() {

	SDL_DestroyTexture(sprite_tex);
	SDL_FreeSurface(sprite_sheet);

}
