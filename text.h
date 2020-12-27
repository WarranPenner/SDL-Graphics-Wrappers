#pragma once
#include <SDL_ttf.h>
#include <map>
#include <string>
#include "texture.h"

class Text : public Texture {
public:
	void init(Window* w, std::string ttfPath, int size);
	void write(std::string text, std::pair<int, int> pos); 

	void setColor(SDL_Color c);
	void setStyle(int ttfStyleBitmask);
	void resetStyle();
private:
	std::string text_ = "";
	TTF_Font* font_ = nullptr;
	SDL_Color color_ = {0xFF, 0xFF, 0xFF, 0xFF};

	void createTexture();
};