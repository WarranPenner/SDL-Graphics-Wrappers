#include "sdlApp.h"

SDLApp::SDLApp() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL failed to initialize!%s\n", SDL_GetError());
		return;
	}

	mainWindow_.createWindow();
}

SDLApp::~SDLApp() {
	mainWindow_.free();
	SDL_Quit();
}

void SDLApp::run() {
	bool quit = false;
	SDL_Event e;
	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}

			mainWindow_.handleEvent(e);
		}

		mainWindow_.render();
	}
}