#pragma once
#include <SDL.h>
#include <stdio.h>
#include <vector>
#include "window.h"

class SDLApp {
public:
	SDLApp();
	~SDLApp();
	void run();
private:
	Window mainWindow_;
	bool graphicsInitialized_ = false;
	const int WINDOW_W_ = 640, WINDOW_H_ = 480;
};