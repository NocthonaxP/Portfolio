#include "stdafx.h"
#include "Background.h"

Background::Background(Window *Win, int player_speedo, bool want_frame) :
	Win(Win), speed(player_speedo) {


	// initialises whole class and checks for failure 
	if (!init(want_frame)) {
		cerr << "Can't initalise Background class" << endl;
		cerr << "Bg class failed" << endl << SDL_GetError() << endl;
	}

}

bool Background::init(bool want_frame) {

	IMG_Init(IMG_INIT_PNG);
	
	// loads background pic

	sur_background = IMG_Load("res/world_test.png");
	if (sur_background == nullptr) {
		cerr << "Couldnt load sur_bg" << endl << SDL_GetError() << endl;
		return 0;
	}
	
	// pic that others will be blit to, just ranom gibberish is fine enough, 
	// it cant be empty bcs you cant put stuff into nothing   

	sur_world = IMG_Load("res/world_test.png");
	if (sur_world == nullptr) {
		cerr << "Couldnt load sur_wrld" << endl << SDL_GetError() << endl;
		return 0;
	}

	// loads picture for helper frame 

	sur_picture = IMG_Load("res/frame.png");
	if (sur_picture== nullptr) {
		cerr << "Couldnt load sur_pic" << endl << SDL_GetError() << endl;
		return 0;
	}

	// sets camera size 

	set_camera_size();
	// sets dimenison of the frames that decide move_lock 
	set_limiters_size();

	cout << camera.w << camera.h << rect_left.w << rect_left.h << endl;
	
	SDL_BlitSurface(sur_background, NULL, sur_world, NULL);
	

	// renders 
	if (want_frame) {

	SDL_BlitSurface(sur_picture, NULL, sur_world, &rect_left);
	SDL_BlitSurface(sur_picture, NULL, sur_world, &rect_right);
}
	tex_world = SDL_CreateTextureFromSurface(Window::renderer, sur_world);
	if (tex_world == nullptr) {
		cerr << "Couldnt create tex_world" << endl << SDL_GetError() << endl;
		return 0;
	}

	cout << SDL_GetError() << endl;
	return true;
}

void Background::draw() {
	
	SDL_RenderCopy(Window::renderer, tex_world, &camera, NULL);

}

void Background::scroll_lock() {

	
	if (camera.x > sur_background->w ) {

		camera.x = sur_background->w ;
	}

	if (camera.x <0) {

		camera.x = 0;
	}
}

void Background::destroy() {

	SDL_FreeSurface(sur_world);
	SDL_FreeSurface(sur_background);
	SDL_FreeSurface(sur_picture);

	SDL_DestroyTexture(tex_world);
	

}

void Background::move_camera(int offset) {
	camera.x += offset;

}

void Background::set_camera_size() {
	
		camera = { 0, 0, 1600, 900 };
		
	cout << "surface size :" << sur_world->w << ", " << sur_world->h << endl;

}

void Background::set_limiters_size() {	

	rect_left = { 0, 0, 800, 900 };
	rect_right = { 7200 , 0, 800, 900 };

}