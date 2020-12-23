#pragma once
#include <SDL.h>
#include <stdio.h>
#include <vector>
#include "texture.h"

class SDLApp {
public:
	SDLApp();
	~SDLApp();
	void run();
private:
	Window mainWindow_;
	SDL_Renderer* renderer_;
	Texture texture_;
	const int WINDOW_W_ = 640, WINDOW_H_ = 480;
	const std::string APP_NAME_ = "SDL App";
};