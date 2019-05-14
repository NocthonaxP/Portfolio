#include "stdafx.h"
#include "Text.h"

Text::Text(SDL_Renderer *renderer, const string &font_path, int font_size, const string &message_text, const SDL_Color &color) {

	if (TTF_Init() == -1) {
		cerr << "Failed to initialize ttf" << endl;
	}

	m_text_texture = loadFont(renderer, font_path, font_size, message_text, color);
	SDL_QueryTexture(m_text_texture, nullptr, nullptr, &m_text_rectangle.w, &m_text_rectangle.h);

	if (TTF_Init() == -1) {
		cerr << "Failed to initialize ttf" << endl;
	}
}

void Text::display(int x, int y, SDL_Renderer *renderer) const {

	m_text_rectangle.x = x;
	m_text_rectangle.y = y;

	SDL_RenderCopy(renderer, m_text_texture, nullptr, &m_text_rectangle);

}

SDL_Texture *Text::loadFont(SDL_Renderer *renderer, const string &font_path, int font_size, const string &message_text, const SDL_Color &color) {

	TTF_Font *font = TTF_OpenFont(font_path.c_str(), font_size);

	if (!font) {
		cerr << "Couldnt initalize the load font" << endl;
	}

	auto text_surface = TTF_RenderText_Solid(font, message_text.c_str(), color);

	if (!text_surface) {
		cerr << "Failed to initialize the text surface" << endl;
	}

	SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

	if (!text_texture) {
		cerr << "Failed to initalize text_texture" << endl;
	}

	SDL_FreeSurface(text_surface);

	return text_texture;
}

void Text::destroy() {

	TTF_Quit();
}
