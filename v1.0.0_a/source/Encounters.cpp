#include "stdafx.h"
#include "Encounters.h"


Encounters::Encounters(Background *bg, Player *player, const string &texture_path, 
	int width, int height, int x, int y, int x_offset, int y_offset, int state_num, bool wall_en) :
	O_BG(bg), O_Player(player), file_path(texture_path), w(width), h(height),
	x(x), y(y), x_offset(x_offset), y_offset(y_offset), number_of_states(state_num), enable_wall(wall_en) {


	// provjerava ispravnost postavljanja pocetnih vrijednosti 
	if (!init()) {
		cerr << "Cant initialise encounter with path:"<< texture_path << SDL_GetError() << endl; 
	}
	
}


Encounters::~Encounters() {

}


bool Encounters::init() {

	//ucitavanje slike
	actor_surface = IMG_Load(file_path.c_str()); 
	 

	//provjera uspjesnoti ucitavanja
	if (actor_surface == nullptr) {
		cerr << "Cant load surface " << file_path<< endl << SDL_GetError() << endl; 
		return 0; 
	}

	// postavljanje vrijednosti za pravokutnik na slici 
	tex_selector = { 0, 0, x_offset, y_offset }; 

	// izrada teksture iz površine
	actor_tex = SDL_CreateTextureFromSurface(Window::renderer, actor_surface); 

	// provjera uspjesnosti izrade teksture
	if (actor_tex == nullptr) {
		cerr << "Cant create texture from surface at" << file_path << endl << SDL_GetError() << endl; 
		return 0; 
	}

	//oslobaðanje memorije koje zauzima površina koja se vise ne koristi  
	SDL_FreeSurface(actor_surface); 
	actor_surface = nullptr;

	//vraca 1 ako je sve uspjesno ili 0 ako nije
	return 1; 
}

void Encounters::check_pos() {

	//proverava da li je igrac u dometu za kontakt sa susretom 
	if (O_BG->get_camera_x() + O_Player->get_pos_x() >= x - 100 &&
		O_BG->get_camera_x() + O_Player->get_pos_x() <= x && is_attacking) {


		if (enable_wall) {
			curr_state_num++;

			if (curr_state_num == number_of_states / 2) {
				//promjena stanja na srednje stanje
				tex_selector.x += x_offset;

			}
			else if (curr_state_num == number_of_states) {
				if (!passed) {
					//zadnje stanje, predeno stanje
					tex_selector.y += y_offset;
					passed = 1;
				}		
			}
		}
		else {
			//ukoliko nema potrebe za zidom nema se niti sto 
			//prijeci te se automatski gleda kao prijedeno 
			passed = 1; 
		}	
	}
	is_attacking = 0;
}


void Encounters::draw() {

	//postavljanje pozcije na koju se rendera u svijetu 
	encouter_actor = { x-O_BG->get_camera_x(), y, w, h }; 

	//kopiraju sadrzaj teksture u renderer
	SDL_RenderCopy(Window::renderer, actor_tex, &tex_selector, &encouter_actor);

}


void Encounters::destroy() {

	//oslobadanje memorije
	SDL_DestroyTexture(actor_tex); 
	SDL_FreeSurface(actor_surface); 
	actor_tex = nullptr; 
	actor_tex = nullptr; 
}