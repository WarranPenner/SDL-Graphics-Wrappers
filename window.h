#pragma once
#include <SDL.h>
#include <string>
#include "viewport.h"

class Window {
public:
	void init(std::string title, int w, int h);
	~Window();

	void paint(SDL_Texture* t, SDL_Rect r);
	void paint(SDL_Texture* t, SDL_Rect r, SDL_Rect* clip,
		double angle, SDL_RendererFlip f = SDL_FLIP_NONE);
	// The following primitive-drawing functions aren't designed for viewports.
	void drawLine(SDL_Point p1, SDL_Point p2, SDL_Color c);
	void drawPoint(SDL_Point p, SDL_Color c);
	void drawRect(SDL_Rect r, SDL_Color c);
	void render();
	void handleEvent(SDL_Event& e);
	void focus();

	void setViewport(Viewport* vp);
	static void setBlendMode(SDL_Texture* t,
		SDL_BlendMode bmode = SDL_BLENDMODE_BLEND);
	static void setAlpha(SDL_Texture* t, Uint8 alpha = 255);
	void setFullscreen();
	void setWindowed();
	void setWindowSize(int w, int h);
	void setNativeSize(int w, int h);

	int getWidth();
	int getHeight();
	SDL_Window* getWindow();
	SDL_Renderer* getRenderer();

	bool hasMouseFocus();
	bool hasKeyboardFocus();
	bool isMinimized();
	bool isShown();
private:
	SDL_Window* sdlWindow_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;
	Viewport* viewport_ = nullptr;

	int windowID_ = -1;
	int w_ = 0, h_ = 0;
	int nativeW_ = w_, nativeH_ = h_;
	const bool DEFAULT_FULL_SCREEN_ = false;
	bool fullScreen_ = DEFAULT_FULL_SCREEN_;
	bool	mouseFocused_ = false,	keyboardFocused_ = false,
			minimized_ = false,		shown_ = false,
			resizable_ = true;
	SDL_Color BG_COLOR_ = {0x00, 0x00, 0x00, 0x00};
};