#pragma once
#include <SDL.h>
#include <stdio.h>
#include <sstream>

class Window {
public:
	~Window();
	void init(std::string title, int w = -1, int h = -1);
	SDL_Texture* loadTexture(std::string imgPath);
	void handleEvent(SDL_Event& e);
	void focus();
	void render();

	void paint(SDL_Texture* t, SDL_Rect r);
	void paint(SDL_Texture* t, SDL_Rect r, int angle, SDL_Rect clip, 
		SDL_RendererFlip f, Uint8 alpha);
	

	int getWidth();
	int getHeight();

	bool hasMouseFocus();
	bool hasKeyboardFocus();
	bool isMinimized();
	bool isShown();
private:
	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;
	int windowID_ = -1;

	const int DEF_W_ = 640, DEF_H_ = 480;
	int w_ = 0, h_ = 0;
	bool resizable = true;
	bool mouseFocused_ = false;
	bool keyboardFocused_ = false;
	bool fullScreen_ = false;
	bool minimized_ = false;
	bool shown_ = false;

	SDL_Color BG_COLOR_ = {0x2F, 0x4F, 0x4F, 0xFF};
	const SDL_Color COLOR_KEY_ = {0x78, 0x6e, 0x64, 0xFF};
	// Transparent pixel color for BMP textures.
	const SDL_BlendMode BLEND_MODE_ = SDL_BLENDMODE_BLEND;
};