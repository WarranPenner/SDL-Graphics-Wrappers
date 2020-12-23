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
		window_ = SDL_CreateWindow(title.c_str(),
									SDL_WINDOWPOS_UNDEFINED,
									SDL_WINDOWPOS_UNDEFINED,
									w,
									h,
									SDL_WINDOW_SHOWN);
	}

	if (!window_) {
		printf("Window is null!\nSDL Error: %s\n", SDL_GetError());
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
			printf("Renderer is null!\nSDL Error: %s\n", SDL_GetError());
			SDL_DestroyWindow(window_);
			window_ = nullptr;
		} else {
			windowID_ = SDL_GetWindowID(window_);
			shown_ = true;
		}
	}
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
	if (!minimized_) {
		SDL_SetRenderDrawColor(renderer_, 0x2F, 0x4F, 0x4F, 0xFF);
		SDL_RenderClear(renderer_);
		SDL_RenderPresent(renderer_);
	}
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

