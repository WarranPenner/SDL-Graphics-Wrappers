#pragma once
#include <SDL.h>
#include "window.h"

class Texture {
public:
	~Texture();
	void init (SDL_Texture* t, Window* w, int x = 0, int y = 0);
	void paint();

	void setPosition(int x, int y);
	void setDimensions(int w, int h); 
	void setClip(int x, int y, int w, int h);
	void setAngle(int a);
	void setAlpha(int a);
	void setFlip(SDL_RendererFlip f);
private:
	SDL_Texture* texture_ = nullptr;
	Window* window_ = nullptr;

	bool initialized_ = false;
	SDL_Rect rect_ = { 0 }, clip_ = { 0 }; 
	int angle_ = 0;
	Uint8 alpha_ = 255;
	SDL_RendererFlip flip_ = SDL_FLIP_NONE;
};