#pragma once


#include "SDL_ttf.h"
#include <string>
#include <iostream>

using namespace std;

class Text {


private:

	SDL_Texture *m_text_texture = nullptr;
	mutable SDL_Rect m_text_rectangle;
	const string message_text;

public:

	Text(SDL_Renderer *renderer, const string &font_path, int font_size, const string &message_text, const SDL_Color &color);

	void display(int x, int y, SDL_Renderer *renderer) const;
	static SDL_Texture *loadFont(SDL_Renderer *renderer, const string &font_path, int font_size, const string &message_text, const SDL_Color &color);
	void destroy();
};
