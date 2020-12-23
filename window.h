#pragma once
#include <SDL.h>
#include <stdio.h>
#include <sstream>

class Window {
public:
	~Window();
	void init(std::string title, int w = -1, int h = -1);
	void handleEvent(SDL_Event& e);
	void focus();
	void render();

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
};