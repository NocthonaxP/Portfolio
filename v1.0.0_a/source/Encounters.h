#pragma once


// ovisio o klasama: 

//vec sarzi zavisnot o klasi Background
#include "Player.h" 


class Encounters{


private:


	/* pravokutnici za poziciju susreta u svijetu 
	 * i pozicija koja se prenosi u renderer
	 */
    SDL_Rect tex_selector; 
	SDL_Rect encouter_actor; 
	
	SDL_Surface *actor_surface = nullptr; 

	SDL_Texture *actor_tex = nullptr; 
	
	// parametri velicine i pozicije
	int w, h, x, y; 

	//put do slike
	const string file_path; 

	//pomak pravokutnika na slici
	int x_offset; 
	int y_offset;

	
	// broj kontakata
	int number_of_states; 
	int curr_state_num=0; 

	//provjera kontakta
	bool is_attacking=0; 
	
	//provjera prisutnosti
	bool is_in; 

	//provjera prolaska prepreke
	bool passed = 0; 
	
	// objketi na klase o kojima ovisi ova klasa
	Background *O_BG; 
	Player *O_Player;

	// inicjalizacija pocetnih vrijednosti
	bool init(); 

	//potreba za nevidljivim zidom
	bool enable_wall; 
	
		
	

public:

	//konsturktor i dekonstruktor 
	Encounters(Background *bg, Player *player, const string &texture_path,
		int width, int height, int x, int y, int x_offset, int y_offset, int state_num, bool wall_en);
	~Encounters(); 

	//renderaj
	void draw();

	//provjera kontakta
	void check_if_attacking(bool attack) { is_attacking = attack; }

	//provjera pozicije 
	void check_pos();

	//oslobada memoriju 
	void destroy(); 

	// traži osnovne parametre velicine i pozicije
	int get_pos_x() { return x;  }
	int get_pos_y() { return y;  }
	int get_size_h() { return h; }
	int get_size_w() { return w; }

	//provjeri prolatak i potrebu za nevidljivim zidom 
	bool chek_if_passed() { return passed;  }
	bool get_wall_pref() { return enable_wall; }
};

