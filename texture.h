#pragma once
#include <SDL.h>
#include "window.h"

class Texture {
public:
	void init(Window* w, std::string imgPath, int x = 0, int y = 0);
	~Texture();

	void paint();
	void setPosition(int x, int y);
	void setDimensions(int w, int h);
	void resetDimensions();
	void setClip(int x, int y, int w, int h);
	void setAngle(int a);
	void setAlpha(Uint8 a);
	void setFlip(SDL_RendererFlip f);
	const SDL_Rect* getRect();
protected:
	SDL_Texture* sdlTexture_ = nullptr;
	Window* window_ = nullptr;

	bool initialized_ = false;
	SDL_Rect rect_ = { 0, 0, 0, 0 }, clip_ = rect_;
	int angle_ = 0;
	SDL_RendererFlip flip_ = SDL_FLIP_NONE;
	Uint8 alpha_ = 255;
	const SDL_BlendMode BLEND_MODE_ = SDL_BLENDMODE_BLEND;
	const SDL_Color COLOR_KEY_ = { 0x78, 0x6e, 0x6e, 0xFF };

	void loadFile(std::string path);
};