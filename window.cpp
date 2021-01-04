#include "window.h"

void Window::init(std::string title, int w, int h) {
	nativeW_ = w_ = w;
	nativeH_ = h_ = h;

	if (resizable_) {
		sdlWindow_ = SDL_CreateWindow(	title.c_str(),
										SDL_WINDOWPOS_UNDEFINED,
										SDL_WINDOWPOS_UNDEFINED,
										w_,
										h_,
										SDL_WINDOW_SHOWN |
										SDL_WINDOW_RESIZABLE);
	} else {
		sdlWindow_ = SDL_CreateWindow(	title.c_str(),
										SDL_WINDOWPOS_UNDEFINED,
										SDL_WINDOWPOS_UNDEFINED,
										w_,
										h_,
										SDL_WINDOW_SHOWN);
	}

	if (!sdlWindow_) {
		printf("ERROR: Window is null!\n");
		printf("SDL error: %s\n", SDL_GetError());
	} else {
		mouseFocused_ = true;
		keyboardFocused_ = true;

		renderer_ = SDL_CreateRenderer(	sdlWindow_,
										-1,
										SDL_RENDERER_ACCELERATED |
										SDL_RENDERER_PRESENTVSYNC);
		if (!renderer_) {
			printf("ERROR: Renderer is null!\n");
			printf("SDL error: %s\n", SDL_GetError());
			SDL_DestroyWindow(sdlWindow_);
			sdlWindow_ = nullptr;
		} else {
			windowID_ = SDL_GetWindowID(sdlWindow_);
			shown_ = true;
		}
	}

	if (DEFAULT_FULL_SCREEN_) {
		setFullscreen();
	}

	SDL_RenderSetLogicalSize(renderer_, nativeW_, nativeH_);
}

Window::~Window() {
	if (renderer_) {
		SDL_DestroyRenderer(renderer_);
	}
	if (sdlWindow_) {
		SDL_DestroyWindow(sdlWindow_);
	}
}

void Window::paint(SDL_Texture* t, SDL_Rect r) {
	if (!viewport_) {
		SDL_RenderCopy(renderer_, t, nullptr, &r);
		return;
	}

	SDL_Rect vp = viewport_->getRect();
	r.x -= vp.x;
	r.y -= vp.y;

	SDL_RenderCopy(renderer_, t, nullptr, &r);
}

void Window::paint(SDL_Texture* t, SDL_Rect r, SDL_Rect* clip,
	double angle, SDL_RendererFlip f) {
	if (!viewport_) {
		SDL_RenderCopyEx(renderer_, t, clip, &r, angle, nullptr, f);
		return;
	}

	SDL_Rect vp = viewport_->getRect();
	r.x -= vp.x;
	r.y -= vp.y;

	SDL_RenderCopyEx(renderer_, t, clip, &r, angle, nullptr, f);
}

void Window::drawLine(SDL_Point p1, SDL_Point p2, SDL_Color c) {
	SDL_SetRenderDrawColor(renderer_, c.r, c.g, c.b, c.a);
	SDL_RenderDrawLine(renderer_, p1.x, p1.y, p2.x, p2.y);
}

void Window::drawPoint(SDL_Point p, SDL_Color c) {
	SDL_SetRenderDrawColor(renderer_, c.r, c.g, c.b, c.a);
	SDL_RenderDrawPoint(renderer_, p.x, p.y);
}

void Window::drawRect(SDL_Rect r, SDL_Color c) {
	SDL_SetRenderDrawColor(renderer_, c.r, c.g, c.b, c.a);
	SDL_RenderFillRect(renderer_, &r);
	SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 0);
}

void Window::render()
{
	if (minimized_) {
		return;
	}

	SDL_RenderPresent(renderer_);
	SDL_SetRenderDrawColor(renderer_, BG_COLOR_.r, BG_COLOR_.g,
		BG_COLOR_.b, BG_COLOR_.r);
	SDL_RenderClear(renderer_);
}

void Window::handleEvent(SDL_Event& e) {
	if (e.window.windowID != windowID_)
		return;

	switch (e.window.event) {
	case SDL_WINDOWEVENT_SIZE_CHANGED:	w_ = e.window.data1;
										h_ = e.window.data2;
	case SDL_WINDOWEVENT_EXPOSED:		SDL_RenderPresent(renderer_);	break;
	case SDL_WINDOWEVENT_SHOWN:			shown_ = true;					break;
	case SDL_WINDOWEVENT_HIDDEN:		shown_ = false;					break;
	case SDL_WINDOWEVENT_ENTER:			mouseFocused_ = true;			break;
	case SDL_WINDOWEVENT_LEAVE:			mouseFocused_ = false;			break;
	case SDL_WINDOWEVENT_FOCUS_GAINED:	keyboardFocused_ = true;		break;
	case SDL_WINDOWEVENT_FOCUS_LOST:	keyboardFocused_ = false;		break;
	case SDL_WINDOWEVENT_MINIMIZED:		minimized_ = true;				break;
	case SDL_WINDOWEVENT_MAXIMIZED:		minimized_ = false;				break;
	case SDL_WINDOWEVENT_RESTORED:		minimized_ = false;				break;
	case SDL_WINDOWEVENT_CLOSE:			SDL_HideWindow(sdlWindow_);		break;
	}
}

void Window::focus()
{
	if (!shown_) {
		SDL_ShowWindow(sdlWindow_);
	}

	SDL_RaiseWindow(sdlWindow_);
}

void Window::setViewport(Viewport* vp) {
	if (!vp->isInitialized()) {
		printf("ERROR: Uninitialized viewport sent to window!\n");
		return;
	}

	viewport_ = vp;
}

void Window::setBlendMode(SDL_Texture* t, SDL_BlendMode bMode) {
	SDL_SetTextureBlendMode(t, bMode);
}

void Window::setAlpha(SDL_Texture* t, Uint8 alpha) {
	SDL_SetTextureAlphaMod(t, alpha);
}

void Window::setFullscreen() {
	SDL_SetWindowFullscreen(sdlWindow_, SDL_WINDOW_FULLSCREEN_DESKTOP);
	SDL_RenderSetLogicalSize(renderer_, nativeW_, nativeH_);
}

void Window::setWindowed() {
	SDL_SetWindowSize(sdlWindow_, w_, h_);
	SDL_SetWindowPosition(sdlWindow_, SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED);
}

void Window::setWindowSize(int w, int h) {
	w_ = w;
	h_ = h;
	SDL_SetWindowSize(sdlWindow_, w_, h_);
}

void Window::setNativeSize(int w, int h) {
	nativeW_ = w;
	nativeH_ = h;
	SDL_RenderSetLogicalSize(renderer_, nativeW_, nativeH_);
}

int Window::getWidth() {
	return nativeW_;
}

int Window::getHeight() {
	return nativeH_;
}

SDL_Window* Window::getWindow() {
	return sdlWindow_;
}

SDL_Renderer* Window::getRenderer() {
	return renderer_;
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