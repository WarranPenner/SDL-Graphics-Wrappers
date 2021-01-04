#pragma once
#include "sdlApp.h"

SDLApp::SDLApp() {
	if (SDL_Init((SDL_INIT_VIDEO) == 0)) {
		printf("ERROR: SDL_INIT has failed!\n");
		printf("SDL error: %s\n", SDL_GetError());
	}
	if (TTF_Init() < 0) {
		printf("ERROR: SDL_TTF could not initialize!\n");
		printf("SDL error: %s", TTF_GetError());
	}

	mainWindow_.init(APP_NAME_, WINDOW_W_, WINDOW_H_);
	mainWindow_.setWindowSize(WINDOW_W_, WINDOW_H_);
	mainWindow_.setNativeSize(NATIVE_DISP_W_, NATIVE_DISP_H_);

	// For demo purposes:
	picture_.init(&mainWindow_, "picture.bmp");
	message_.init(&mainWindow_, "timesNewRoman.ttf", 48);
}

SDLApp::~SDLApp() {
	SDL_Quit();
	TTF_Quit();
}

void SDLApp::run() {
	bool running = true;
	SDL_Event e;

	while (running) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				running = false;
			}

			mainWindow_.handleEvent(e);
		}

		// For demo purposes:
		picture_.paint();
		message_.write("Hello world!", {10, 40});

		mainWindow_.render();
	}
}