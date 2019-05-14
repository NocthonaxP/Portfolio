#include "stdafx.h"	
#include "Window.h"

SDL_Renderer *Window::renderer;

Window::Window(const string &title, int width, int height) :
	m_title(title), m_width(width), m_height(height) {

	

	if (!init()) {
		m_closed = true;
	}

	// makes pointers share variables adress
	// size of the window is stored in the pointers and for simplicity they overwrite varibles
	// pointers are used only bcs function SDL_GetWindowSize() requires them 
	measured_w = &m_width;
	measured_h = &m_height;
}

Window::Window() {
}

bool Window::init() {

	

   // initialises and check for success of initalisation 
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		cerr << "Failed to initalise sdl" << endl;
		return false;
	}
	SDL_SetHintWithPriority(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "1", SDL_HINT_OVERRIDE);
	// creates window that is resizeable by dragging border of the window
	
	m_window = SDL_CreateWindow(
		m_title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		m_width, m_height, 
		NULL
	);

	// checks if window was created
	if (m_window == nullptr) {
		cerr << "Failed to create a window in Window init" << endl;
		return false;
	}

	// stvara renderer koji je sinkroniziran sa brzinom osvježavanja ekrana
	renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);

	// checks if renderer was created 
	if (renderer == nullptr) {
		cerr << "Failed to create a renderer in Window init" << endl;
		return false;
	}
	
	return true;
}

void Window::present() {
	SDL_RenderPresent(renderer);
}

void Window::clear()  const {

	//displays whole content of renderer to the screen
	
	SDL_RenderClear(renderer); 

	//this shows the new, red contents of the window, everything was drawn behind the scenes up untill this, you first make
	//SDL_SetRenderDrawColor(renderer, 250, 0, 0, 255);
	//SDL_RenderClear(renderer);
	//clears the entire screen to our selected colour
}



void Window::set_fullscreen() {


	// set window to borderless fullscreen 
	SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
}

void Window::destroy() {

	// some ppl rly want to see the world burn 

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}


void Window::get_size() {

	// measure the size of the screen saves the data into the pointers 

	SDL_GetWindowSize(m_window, measured_w, measured_h);

 	
}

int Window::get_Height() {

	// measure size, return it 
//	get_size();
	//return (m_height / 10)*10;
	return m_height;
}

int Window::get_Width() {

	// measure size, return it 
	//get_size();

//	return (m_width /10) * 10;
	return m_width;

}

