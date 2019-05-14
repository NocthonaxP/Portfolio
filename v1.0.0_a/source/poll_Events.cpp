#include "stdafx.h"
#include "poll_Events.h"


poll_Events::poll_Events(Window *window, Player *player, Sound *sound, Background *background,
	Button *item1, Button *item2, Button *button, GUI *gui, Encounters *EGrass, Encounters *ESnake, 
	Encounters *ETree, Encounters *EDoor) :
	O_Window(window), O_Player(player), O_Sound(sound), O_Background(background), Item1(item1), 
	Item2(item2), O_Button(button), O_GUI(gui) {

	O_Encounters[0] = EGrass;
	O_Encounters[1] = ESnake;
	O_Encounters[2] = ETree;
	O_Encounters[3] = EDoor;

}


poll_Events::~poll_Events() {
}


void poll_Events::global_Events() {


	SDL_Event event;
	if (SDL_PollEvent(&event)) {


		if (event.type == SDL_QUIT) {

			O_Window->close_window(1);
		}

		switch (event.type) {

		case SDL_KEYUP:
			//resetiranje animacije u stajacu poziciju kad je otpustena tipka za hodanje

			switch (event.key.keysym.sym) {

			case SDLK_LEFT:

			case SDLK_RIGHT:

			case SDLK_UP:

			case SDLK_DOWN:
				
			case SDLK_SPACE:
				
				
				O_Player->direction = 0;
				O_Player->sprite_manager();
	 
			}
			break;


			//keyboard events
		case SDL_KEYDOWN:

			switch (event.key.keysym.sym) {

				{
					/*
					*~~~~~~~~~~~~~~~~//oOo// CAMERA //oOo//~~~~~~~~~~~~~~~~
					*~~~~~~~~~~~~~~~~//oOo// PLAYER //oOo//~~~~~~~~~~~~~~~~
					*/



			case SDLK_LEFT:

				if (O_Background->camera_move_free) {
					O_Background->move_camera(-O_Player->get_speed());
					O_Background->scroll_lock();
					cout << "Camera " << O_Background->get_camera_x() << endl;
				}

				O_Player->direction = 2;
				O_Player->sprite_manager();
				if (O_Player->player_move_free) {
					O_Player->set_pos_x(O_Player->get_pos_x() - O_Player->get_speed());
					cout << "Sharkie ( " << O_Player->get_pos_x() << "," << O_Player->get_pos_y() << " )" << endl;
				}
				O_Player->mov_edge();

				break;

			case SDLK_RIGHT:

				if (O_Background->camera_move_free) {
					O_Background->move_camera(O_Player->get_speed());
					O_Background->scroll_lock();
					cout << "Camera " << O_Background->get_camera_x() << endl;
				}


				O_Player->direction = 1;
				O_Player->sprite_manager();
				if (O_Player->player_move_free) {
					O_Player->set_pos_x(O_Player->get_pos_x() + O_Player->get_speed());
					cout << "Sharkie ( " << O_Player->get_pos_x() << "," << O_Player->get_pos_y() << " )" << endl;
				}
				O_Player->mov_edge();

				break;

			case SDLK_UP:
				O_Player->set_pos_y(O_Player->get_pos_y() - O_Player->get_speed());
				cout << "Sharkie ( " << O_Player->get_pos_x() << "," << O_Player->get_pos_y() << " )" << endl;

				O_Player->mov_edge();

				break;


			case SDLK_DOWN:

				O_Player->set_pos_y(O_Player->get_pos_y() + O_Player->get_speed());
				cout << "Sharkie ( " << O_Player->get_pos_x() << "," << O_Player->get_pos_y() << " )" << endl;

				O_Player->mov_edge();

				break;


			case SDLK_SPACE:


				O_Player->direction = 3;
				O_Player->sprite_manager();


				for (int i = 0; i < 3; i++) {
					O_Encounters[i]->check_if_attacking(1);
				}

				O_Sound->play_sfx(); 

				cout << "Space pressed" << endl;
				break;
				}
				//background and player


				{
					/*
					*~~~~~~~~~~~~~~~~//oOo// WINDOW //oOo//~~~~~~~~~~~~~~~~
					*/

			case SDLK_ESCAPE:

				O_Window->close_window(1);
				cout << "Esc" << endl;
				break;


				}
				//window

				{

					/*
					*~~~~~~~~~~~~~~~~//oOo// SOUND //oOo//~~~~~~~~~~~~~~~~
					*/

			case SDLK_w:
				if (O_Player->get_wpn_selector() == 1) {
					O_Player->set_wpn_selector(0);
				}
				else {
					O_Player->set_wpn_selector(1);
				}

				cout << " U changed to wpn " << O_Player->get_wpn_selector() << endl;
				break;

			case SDLK_c:

				O_Player->set_active(!O_Player->get_active());
				break;

			case SDLK_p:
				O_Sound->pause_music();
				break;

			case SDLK_m:
				O_Sound->stop_music();
				break;
				}

				//Sound
				{
			case SDLK_e:

				if (!get_mouse_tracking()) {
					set_mouse_tracking(1);
				}
				else {
					set_mouse_tracking(0);
				}
				break;
				}
				//controling writing mouse pos to conole

				{


			case SDLK_g:
				cout << "Sharkie ( " << O_Player->get_pos_x() << "," << O_Player->get_pos_y() << " )" << endl;
				cout << "Camera " << O_Background->get_camera_x() << endl;
				cout << "Window size (" << O_Window->get_Width() << "," << O_Window->get_Height() << " )" << endl;
				cout << "Camera size (" << O_Background->get_camera_w() << "," << O_Background->get_camera_h() << " )" << endl;
				break;
				}
				break;
			}
			// mouse events (works with touch pad too)
		case SDL_MOUSEBUTTONDOWN:


			switch (event.button.button) {
			case SDL_BUTTON_LEFT:


				Item1->set_key(1);
				Item1->sprite_manager();
				Item2->set_key(1);
				Item2->sprite_manager();
				O_Button->set_key(1);
				O_Button->sprite_manager();

				cout << "Left mouse button pressed" << endl;
				break;
			case SDL_BUTTON_RIGHT:


				Item1->set_key(2);
				Item1->sprite_manager();

				Item2->set_key(2);
				Item2->sprite_manager();
				O_Button->set_key(2);
				O_Button->sprite_manager();


				cout << "Right mouse button pressed" << endl;
				break;

			}
			break;

		case SDL_MOUSEBUTTONUP:


			switch (event.button.button) {
			case SDL_BUTTON_LEFT:


				Item1->set_key(0);
				Item1->sprite_manager();
				Item2->set_key(0);
				Item2->sprite_manager();
				O_Button->set_key(0);
				O_Button->sprite_manager();

				cout << "Left mouse button released" << endl;
				break;
			case SDL_BUTTON_RIGHT:


				Item1->set_key(0);
				Item1->sprite_manager();
				Item2->set_key(0);
				Item2->sprite_manager();
				O_Button->set_key(0);
				O_Button->sprite_manager();


				cout << "Right mouse button released" << endl;
				break;

			}
			break;


		case SDL_MOUSEMOTION:
			mouseX = event.motion.x;
			mouseY = event.motion.y;

			Item1->set_mouse_pos(mouseX, mouseY);
			Item1->sprite_manager();
			Item2->set_mouse_pos(mouseX, mouseY);
			Item2->sprite_manager();



			O_Button->set_mouse_pos(mouseX, mouseY);
			O_Button->sprite_manager();



			if (get_mouse_tracking()) {
				cout << "Mouse pos ( " << mouseX << ", " << mouseY << ")" << endl;
			}
			break;
		}
	}

	if (Item1->get_is_pressed_l()  || Item2->get_is_pressed_r()) {
		O_Window->close_window(1);
	}



}


void poll_Events::lock_manager() {


	// opci uvjeti
	O_Player->player_move_free = true;
	O_Background->camera_move_free = false;

	if (O_Background->get_camera_x() > 0 && O_Background->get_camera_x() < 6400) {

		O_Player->player_move_free = false;
		O_Background->camera_move_free = true;

	}

	//lijevi rub
	if (O_Player->get_pos_x() == O_Background->get_rect_left_w() && O_Background->get_camera_x() == 0) {

		O_Player->player_move_free = true;
		O_Background->camera_move_free = true;

	}

	//desni rub
	if (O_Player->get_pos_x() == O_Background->get_camera_w() / 2 &&
		O_Background->get_camera_x() == O_Background->get_rect_right_x() - O_Background->get_camera_w()/2) {
		O_Player->player_move_free = false;
		O_Background->camera_move_free = true;

	}

	//voda
	if (O_Player->get_pos_x() <= 350 && O_Background->get_camera_x() == 0) {
		O_Player->player_move_free = false;
		O_Background->camera_move_free = true;

		
	}
	else
		if (O_Player->get_pos_x() + O_Background->get_camera_x() > 350 &&
			O_Player->get_pos_x() + O_Background->get_camera_x() < O_Background->get_rect_left_w()) {
			O_Player->player_move_free = true;
			O_Background->camera_move_free = false;
		}

	//blokiranje hoda kod susreta
	for (int i = 0; i < 3; i++) {

			if (O_Player->get_pos_x() + O_Background->get_camera_x() >= O_Encounters[i]->get_pos_x() &&
				!O_Encounters[i]->chek_if_passed()) {

				O_Player->player_move_free = false;
				O_Background->camera_move_free = false;

				if (O_Player->get_pos_x() + O_Background->get_camera_x() == O_Encounters[i]->get_pos_x() + O_Player->get_speed()) {
					O_Player->set_pos_x(O_Encounters[i]->get_pos_x() - O_Background->get_camera_x());
				}


			}

			if (O_Player->get_pos_x() + O_Background->get_camera_x() == O_Encounters[i]->get_pos_x()) {
				O_Player->player_move_free = true;
				O_Background->camera_move_free = false;
			}

		
	}
}  