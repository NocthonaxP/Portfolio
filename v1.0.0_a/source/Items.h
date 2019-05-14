#pragma once

#include "Button.h"

using namespace std;

class Items : public Button{



private:
	
	void drag();
	
	


public:

	Items(Background *bg, const string &texture_path, int width, int height, int x, int y, int select_button, int x_offset, int y_offset);
	void sprite_manager();
	void draw();
};

