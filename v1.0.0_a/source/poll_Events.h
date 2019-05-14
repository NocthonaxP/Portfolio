#pragma once

#include "Master_header.h"


using namespace std;

class poll_Events {

private:

	Window * O_Window;
	Player *O_Player;
	Sound *O_Sound;
	Background *O_Background;
	GUI *O_GUI;
	Encounters *O_Encounters[4];

	Button *O_Button;
	Button *Item1;
	Button *Item2;
	

	int mouseX;
	int mouseY;
	const Uint8* keyState;
	bool mouse_tracking = false;
	bool locked_house = 1;


	int get_player_world_x() {
		return O_Player->get_pos_x() + O_Background->get_camera_x();
	}


public:

	poll_Events(Window *window, Player *player, Sound *sound, Background *background, Button *item1, Button *item2, Button *button, GUI *gui, Encounters *EGrass, Encounters *ESnake, Encounters *ETree, Encounters *EDoor);
	~poll_Events();

	void lock_manager();
	void global_Events();
	void set_mouse_tracking(bool enable_tracking) { mouse_tracking = enable_tracking; }
	bool get_mouse_tracking() { return mouse_tracking; }
	int get_mouse_y() { return mouseY; };
	int get_mouse_x() { return mouseX; };

	

};

