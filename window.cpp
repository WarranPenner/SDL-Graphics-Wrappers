#include "window.h"

Window::~Window() {
	if (window_) {
		SDL_DestroyWindow(window_);
	}
}

void Window::init(std::string title, int w, int h) {
	if (w == -1) {
		w = DEF_W_;
	}
	if (h == -1) {	
		h = DEF_H_;
	}

	if (resizable) {
		window_ = SDL_CreateWindow(	title.c_str(),
									SDL_WINDOWPOS_UNDEFINED, 
									SDL_WINDOWPOS_UNDEFINED, 
									w, 
									h,
									SDL_WINDOW_SHOWN |
									SDL_WINDOW_RESIZABLE);
	} else {
		window_ = SDL_CreateWindow(	title.c_str(),
									SDL_WINDOWPOS_UNDEFINED,
									SDL_WINDOWPOS_UNDEFINED,
									w,
									h,
									SDL_WINDOW_SHOWN);
	}

	if (!window_) {
		printf("Window is null!\nSDL error: %s\n", SDL_GetError());
	} else {
		mouseFocused_ = true;
		keyboardFocused_ = true;
		w_ = w;
		h_ = h;

		renderer_ = SDL_CreateRenderer(	window_,
										-1,
										SDL_RENDERER_ACCELERATED |
										SDL_RENDERER_PRESENTVSYNC);
		if (!renderer_) {
			printf("Renderer is null!\nSDL error: %s\n", SDL_GetError());
			SDL_DestroyWindow(window_);
			window_ = nullptr;
		} else {
			windowID_ = SDL_GetWindowID(window_);
			shown_ = true;
		}
	}
}

SDL_Texture* Window::loadTexture(std::string imgPath) {	
	if (imgPath.at(imgPath.length() - 1) != *"p" &&
		imgPath.at(imgPath.length() - 2) != *"m" &&
		imgPath.at(imgPath.length() - 3) != *"b" &&
		imgPath.at(imgPath.length() - 4) != *".") {
		printf("Image file '%s' has an invalid type!\n", imgPath.c_str());
	}

	SDL_Surface* s = SDL_LoadBMP(imgPath.c_str());
	if (!s) {
		printf("Surface for '%s' is null!\n", imgPath.c_str());
		printf("SDL error: %s\n", SDL_GetError());
		return nullptr;
	}

	SDL_SetColorKey(s, SDL_TRUE, SDL_MapRGB(s->format, COLOR_KEY_.r,
		COLOR_KEY_.g, COLOR_KEY_.b));
	SDL_Texture* t = nullptr;
	t = SDL_CreateTextureFromSurface(renderer_, s);

	if (!t) {
		printf("Texture for '%s' is null!\n", imgPath.c_str());
		printf("SDL error: %s\n", SDL_GetError());
	}

	SDL_SetTextureBlendMode(t, BLEND_MODE_);
	SDL_FreeSurface(s);
}

void Window::handleEvent(SDL_Event& e) {
	if (e.type == SDL_WINDOWEVENT && e.window.windowID == windowID_) {
		bool updateCaption = false;

		switch (e.window.event) {
		case SDL_WINDOWEVENT_SHOWN:
			shown_ = true;
			break;
		case SDL_WINDOWEVENT_HIDDEN:
			shown_ = false;
			break;
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			w_ = e.window.data1;
			h_ = e.window.data2;
			SDL_RenderPresent(renderer_);
			break;
		case SDL_WINDOWEVENT_EXPOSED:
			SDL_RenderPresent(renderer_);
			break;
		case SDL_WINDOWEVENT_ENTER:
			mouseFocused_ = true;
			updateCaption = true;
			break;
		case SDL_WINDOWEVENT_LEAVE:
			mouseFocused_ = false;
			updateCaption = true;
			break;
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			keyboardFocused_ = true;
			updateCaption = true;
			break;
		case SDL_WINDOWEVENT_FOCUS_LOST:
			keyboardFocused_ = false;
			updateCaption = true;
			break;
		case SDL_WINDOWEVENT_MINIMIZED:
			minimized_ = true;
			break;
		case SDL_WINDOWEVENT_MAXIMIZED:
			minimized_ = false;
			break;
		case SDL_WINDOWEVENT_RESTORED:
			minimized_ = false;
			break;
		case SDL_WINDOWEVENT_CLOSE:
			SDL_HideWindow(window_);
			break;
		}
	}
}

void Window::focus()
{
	if (!shown_) {
		SDL_ShowWindow(window_);
	}

	SDL_RaiseWindow(window_);
}

void Window::render()
{
	if (minimized_) {
		return;
	}

	SDL_RenderPresent(renderer_);
	SDL_SetRenderDrawColor(	renderer_,		BG_COLOR_.r,
							BG_COLOR_.g,	BG_COLOR_.b,
							BG_COLOR_.r);
	SDL_RenderClear(renderer_);
}

void Window::paint(SDL_Texture* t, SDL_Rect r) {

}

void Window::paint(SDL_Texture* t, SDL_Rect r, int angle, SDL_Rect clip,
	SDL_RendererFlip f, Uint8 alpha) {
	SDL_RenderCopyEx(renderer_,	t, &clip, nullptr, angle, nullptr, f);
}

int Window::getWidth() {
	return w_;
}

int Window::getHeight() {
	return h_;
}

bool Window::hasMouseFocus() {
	return mouseFocused_;
}

bool Window::hasKeyboardFocus() {
	return keyboardFocused_;
}

bool Window::isMinimized() {
	return minimized_;
}

bool Window::isShown() {
	return shown_;
}

