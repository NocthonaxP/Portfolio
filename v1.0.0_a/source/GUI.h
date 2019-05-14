#pragma once

#include "Window.h"
#include "Button.h"
#include "Player.h"
#include <SDL_image.h>

class GUI : protected Window {


private:

	
	SDL_Rect frame; //whole pic
	//SDL_Rect foreground_rect; // not using atm
	SDL_Rect hp_orb_rect;
	SDL_Rect scroll_hp;
	SDL_Rect wpn_orb_rect;
	SDL_Rect wpn_orb_select_rect;
	SDL_Rect char_orb_rect;
	SDL_Rect char_orb_select;
	SDL_Rect inv_slot_1_rect;
	SDL_Rect inv_slot_2_rect;
	SDL_Rect inv_slot_3_rect;
	SDL_Rect inv_slot_4_rect;


	SDL_Surface *GUI_pic;
	SDL_Texture *GUI_tex;

	SDL_Surface *foreground;
	SDL_Texture *foreground_tex;

	SDL_Surface *hp_orb;
	SDL_Texture *hp_orb_tex;

	SDL_Surface *wpn_orb;
	SDL_Texture *wpn_orb_tex;

	SDL_Surface *char_orb;
	SDL_Texture *char_orb_tex;

	SDL_Surface *inv_slot_1;
	SDL_Texture *inv_slot_1_tex;

	SDL_Surface *inv_slot_2;
	SDL_Texture *inv_slot_2_tex;

	SDL_Surface *inv_slot_3;
	SDL_Texture *inv_slot_3_tex;

	SDL_Surface *inv_slot_4;
	SDL_Texture *inv_slot_4_tex;


	Player *O_Player;

	
//	Button menu_button;


	int hp_scroll_offset;




public:



	bool init();
	GUI(Player *obj_player);
	~GUI();
	void draw();

	int get_GUI_x() { return frame.x; };
	int get_GUI_y() { return frame.y; };

	int get_GUI_w() { return frame.w; };
	int get_GUI_h() { return frame.h; };

	void destroy();

};

