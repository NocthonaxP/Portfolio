#pragma once

#include "stdafx.h"
#include <SDL.h>
#include <iostream>
#include <string>
#include <SDL_hints.h>
using namespace std;

class Window {



private:

	// reserve space for surface and texture of background

	SDL_Surface *sur_background;
	SDL_Texture *tex_background;
	


protected:

	// makes pointer to a window

	SDL_Window *m_window = nullptr;
	string m_title;

	// is window closed
	bool m_closed = false;

	// initalise (create) all sturctures above
	bool init();


	// dimension of window
	int m_width;
	int m_height;

	// pointers that take same addreses as dimension of the screen
	// used for SDL_GetWindowSize() to store measured size of the current window

	int *measured_w;
	int *measured_h;


public:

	// constructor 
	Window(const string &title, int width, int height);
	Window();

	// pointer to main renderer
	static SDL_Renderer *renderer;

	// returns desired parameter of the screen 
	int get_Width();
	int get_Height();

	// measures current size of the screen 
	void get_size();

	// checks if window is closed
	bool is_closed() const { return m_closed; }

	// closes window 
	void close_window(bool close) { m_closed = close; }

	// make window borderless fullscreen 
	void set_fullscreen();

	// display renderer 
	void clear() const;

	// destroy objects 
	void destroy();

	void present();
};
