#include "stdafx.h"
#include "GUI.h"


GUI::GUI(Player *obj_player) : O_Player(obj_player) {

	if (!init()) {
		cerr << "Can't initialise GUI" << endl;
	}
	

}


GUI::~GUI(){
	
}

bool GUI::init() {

	// offset +40 y 

	IMG_Init(IMG_INIT_PNG);

	frame = { 150, 740 , 1300, 150 };
	//foreground_rect = { 0,550, 1200, 250 };
	hp_orb_rect = { 200, 785, 200, 65 };
	scroll_hp = { 0, 65, 200, 65 };
	wpn_orb_rect = {1200, 785, 200, 65};
	wpn_orb_select_rect = { 0, 0, 200, 65};
	char_orb_rect = {780,752,135,80};
	char_orb_select = { 0, 80, 135, 80 };


	hp_scroll_offset = 0;

	GUI_pic = IMG_Load("res/HUD_result.png");
	//foreground = SDL_LoadBMP("res/listije.bmp");
	hp_orb = IMG_Load("res/blood_liquid_new_result.png");
	
	wpn_orb = IMG_Load("res/wpn_spreadsheet_result.png");

	char_orb = IMG_Load("res/char_spreadsheet_result.png");


	//should put all this tests to separate function, this is getting messy 

	if (GUI_pic == nullptr) {
		cerr << "Cant load GUI picture" << endl;
	}

	/*if (foreground == nullptr) {
		cerr << "Cant load foreground picture" << endl;
	}*/

	if (hp_orb == nullptr) {
		cerr << "Cant load hp_orb picture" << endl;
	}

	if (wpn_orb == nullptr) {
		cerr << "Cant load wpn_orb picture" << endl;
	}

	if (char_orb == nullptr) {
		cerr << "Cant load char_orb picture" << endl;
	}
	

	GUI_tex = SDL_CreateTextureFromSurface(renderer, GUI_pic);
	//foreground_tex = SDL_CreateTextureFromSurface(renderer, foreground);
	hp_orb_tex = SDL_CreateTextureFromSurface(renderer, hp_orb);
	wpn_orb_tex = SDL_CreateTextureFromSurface(renderer, wpn_orb);
	char_orb_tex = SDL_CreateTextureFromSurface(renderer, char_orb);


	if (GUI_tex == nullptr) {
		cerr << "Cant create GUI texture" << endl;
	}

	if (hp_orb_tex == nullptr) {
		cerr << "Cant create hp_orb_tex texture" << endl;
	}

	if (wpn_orb_tex == nullptr) {
		cerr << " Cant create wpn_orb_tex texture " << endl;
	}

	if (wpn_orb_tex == nullptr) {
		cerr << "Cant create wpn_orb_tex texture" << endl;
	}
	return true;
}


 

void GUI::draw() {
	
	hp_scroll_offset ++;
	if (hp_scroll_offset > 540) {
		hp_scroll_offset = 0;
	}

	scroll_hp.x =(int) ( 0.740740 * hp_scroll_offset);
	/*
	 * IK, oddly specific number, it's lenght it has to move thorugh / number of clock ticks (frames) , so in this case 400/540, 
	 * will add exact number ( let PC calculate it itself) but let it stay like this for now, pic is not reseting good bcs I didnt edit it good, 
	 * it's good enough for testing purposes
	 */

	//SDL_RenderCopy(renderer, foreground_tex, NULL, &foreground_rect);

	wpn_orb_select_rect.y = wpn_orb_select_rect.h * O_Player->get_wpn_selector();
	char_orb_select.y = char_orb_select.h * O_Player->get_active();


	SDL_RenderCopy(renderer, hp_orb_tex, &scroll_hp, &hp_orb_rect);
	SDL_RenderCopy(renderer, wpn_orb_tex, &wpn_orb_select_rect, &wpn_orb_rect);
	SDL_RenderCopy(renderer, char_orb_tex, &char_orb_select, &char_orb_rect);
	SDL_RenderCopy(renderer, GUI_tex, NULL, &frame);
	


}

void GUI::destroy() {

	SDL_DestroyTexture(GUI_tex);
	SDL_DestroyTexture(foreground_tex);
	SDL_DestroyTexture(hp_orb_tex);
	SDL_DestroyTexture(wpn_orb_tex);
	SDL_DestroyTexture(char_orb_tex);
	
	SDL_FreeSurface(GUI_pic);
	SDL_FreeSurface(foreground);
	SDL_FreeSurface(hp_orb);
	SDL_FreeSurface(wpn_orb);
	SDL_FreeSurface(char_orb);

}