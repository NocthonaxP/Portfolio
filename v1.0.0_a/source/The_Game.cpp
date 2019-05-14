#include "stdafx.h"
#include "Master_header.h"



void destroy(Window &window, Player &player, Text &text, Background &background, Sound &sound, GUI &gui, Encounters &Snake, Encounters &Grass, Encounters &Tree) {

	//destroy every object in reverse of making it



	
	Tree.destroy(); 
	Grass.destroy();
	Snake.destroy(); 
	sound.destroy();
	text.destroy();
	background.destroy();
	//gui.destroy();
	player.destroy();
	window.destroy();


}


int main(int argc, char **argv) {

	Window *p_window;
	Window Window("What can we do until 1.1.", 1600, 900);


	p_window = &Window;

	Player *p_player;
	Player Player(150, 120, 500, 610, p_window);


	p_player = &Player;


	GUI *p_GUI;
	GUI Gui(p_player);
	p_GUI = &Gui;

	Background *p_background;
	Background Background(p_window, Player.get_speed(), 0); 
	p_background = &Background;

	Text Message(Window::renderer, "res/arial.ttf", 30, "Want to quit?", { 0,255,0,255 });
	Text Text(Window::renderer, "res/arial.ttf", 30, "Završni rad", { 0,255,0,255 });

	Timer TIMER;
	Timer Timer;

	Sound *p_sound;
	Sound Sound;

	p_sound = &Sound;

	Sound.sound_manager();
	Encounters *p_EGrass; 
	Encounters EGrass( p_background, p_player, "res/bushes_test.png", 900, 750, 1800, 50, 700, 500, 4,1);
	p_EGrass = &EGrass; 

	Encounters *p_ESnake;
	Encounters ESnake(p_background, p_player, "res/snek_result.png", 300, 200, 3200, 550, 300, 200, 8,  1);
	p_ESnake = &ESnake;


	Encounters *p_ETree;
	Encounters ETree(p_background, p_player, "res/tree_result.png", 300, 150, 6000, 650, 300, 150, 16, 1);
	p_ETree = &ETree;

	Encounters *p_EDoor;
	Encounters EDoor(p_background, p_player, "res/wall.png", 900, 390, 7300, 500, 75, 75, 16, 1);
	p_EDoor = &EDoor;


	Button *p_button;
	Button Button_Chick(p_background, "res/girl_spread.png", 100, 130, 7500, 600, 1, 743, 1250);
	p_button = &Button_Chick;


	Button item1(p_background, "res/button_l.png", 50, 50, 7500, 540, 1, 75, 75);
	Button *p_item1;
	p_item1 = &item1;


	Button item2(p_background, "res/button_r.png", 50, 50, 7550, 540, 1, 75, 75);
	Button *p_item2;
	p_item2 = &item2;



	poll_Events poll_Event(p_window, p_player, p_sound, p_background, p_item1,p_item2, p_button, p_GUI, p_EGrass, p_ESnake, p_ETree, p_EDoor);

	Sound.play_music();
	/*
	-~~~~~~~~~~~~~~~//!!oOo!!// GAME LOOP //!!oOo!!//~~~~~~~~~~~~~~~-
	*/

	 
	//petlja igre
	while (!Window.is_closed()) {
		// pokretanje timera za provjeru FPSa
		Timer.start();


		// pokretanje timera za zakljuèavanje FPSa
		TIMER.start();
		// test Input for movement (cam and player)

		Window.clear(); 
		poll_Event.lock_manager();

		// test input for everything else
		poll_Event.global_Events();


		//add background to renderer
		Background.draw();


		//checks and renders if encounters are in area

		// add button to renderer
		Button_Chick.draw();
		
		// add text to renderer
		Text.display(200, 20, Window::renderer);
		Message.display(7450-Background.get_camera_x(), 500, Window::renderer); 
	
		
		ESnake.check_pos(); 
		ESnake.draw(); 
		ETree.check_pos(); 
		ETree.draw(); 
		EGrass.check_pos();
		item1.draw(); 
		item2.draw(); 
		// add player to renderer
		Player.draw();

		
		EGrass.draw();
		

		// add GUI to renderer
		Gui.draw();


		// put renderer on screen 
		Window.present();

		// fps timers stops
		Timer.stop();

		// provjerava vrijeme jedne iteracije petlje i podešava ju na 59FPS-a (17ms)
		if (Timer.get_time(0) < Timer.get_frame_time(0)) {
			// ako je iteracija pre brza, kod se zaustavlja i èeka da se cijela iteracija traje 17ms
			SDL_Delay((Uint32)(Timer.get_frame_time(0) - Timer.get_time(0)));
			// zaustavljanje testnog timera
			TIMER.stop();
		}
		
		// provjera efikasnoti zakljuèavanja FPS-a, ispis u konzoli 
		TIMER.get_time(0);

	}


	// cleans memory of all listed objects, using deconstructors would crash the code
	destroy(Window, Player, Text, Background, Sound, Gui, ESnake, EGrass, ETree);
	return 0;

}