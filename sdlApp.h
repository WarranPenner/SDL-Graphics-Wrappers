#pragma once
#include <string>
#include "text.h"

class SDLApp {
public:
	SDLApp();
	~SDLApp();
	void run();
private:
	Window mainWindow_;
	Viewport viewport_;

	const std::string APP_NAME_ = "SDL App";
	const int WINDOW_W_ = 640, WINDOW_H_ = 360;
	const int NATIVE_DISP_W_ = 640,	NATIVE_DISP_H_ = 360;
	bool running_ = true;

	// For demo purposes:
	Texture picture_;
	Text message_;
};