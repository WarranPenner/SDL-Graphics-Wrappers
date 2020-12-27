#include "texture.h"

void Texture::init(Window* w, std::string imgPath, int x, int y) {
	window_ = w;
	loadFile(imgPath);

	rect_.x = x;
	rect_.y = y;
	SDL_QueryTexture(sdlTexture_, nullptr, nullptr, &rect_.w, &rect_.h);
	clip_.w = rect_.w;
	clip_.h = rect_.h;

	if (sdlTexture_ && window_) {
		initialized_ = true;
	}
}

Texture::~Texture() {
	if (sdlTexture_) {
		SDL_DestroyTexture(sdlTexture_);
		sdlTexture_ = nullptr;
	}
}

void Texture::paint() {
	if (initialized_) {
		window_->paint(sdlTexture_, rect_, &clip_, angle_, flip_);
	}
}

void Texture::setPosition(int x, int y) {
	rect_.x = x;
	rect_.y = y;
}

void Texture::setDimensions(int w, int h) {
	rect_.w = w;
	rect_.h = h;
}

void Texture::resetDimensions() {
	if (initialized_) {
		SDL_QueryTexture(sdlTexture_, nullptr, nullptr, &rect_.w, &rect_.h);
	}
}

void Texture::setClip(int x, int y, int w, int h) {
	clip_.x = x;
	clip_.y = y;
	clip_.w = w;
	clip_.h = h;
}

void Texture::setAngle(int a) {
	angle_ = a;
}

void Texture::setAlpha(Uint8 a) {
	alpha_ = a;
}

void Texture::setFlip(SDL_RendererFlip f) {
	flip_ = f;
}

const SDL_Rect* Texture::getRect() {
	return &rect_;
}

void Texture::loadFile(std::string path) {
	if (path.at(path.length() - 1) != *"p" &&
		path.at(path.length() - 2) != *"m" &&
		path.at(path.length() - 3) != *"b" &&
		path.at(path.length() - 4) != *".") {
		printf("ERROR: Texture image '%s' is not a BMP file!\n", path.c_str());
		printf("SDL error: %s\n", SDL_GetError());
	}

	SDL_Surface* s = SDL_LoadBMP(path.c_str());
	if (!s) {
		printf("ERROR: Surface for '%s' is null!\n", path.c_str());
		printf("SDL error: %s\n", SDL_GetError());
		return;
	}

	SDL_SetColorKey(s, SDL_TRUE, SDL_MapRGB(s->format, COLOR_KEY_.r,
		COLOR_KEY_.g, COLOR_KEY_.b));
	sdlTexture_ = SDL_CreateTextureFromSurface(window_->getRenderer(), s);

	if (!sdlTexture_) {
		printf("ERROR: Texture for '%s' is null!\n", path.c_str());
		printf("SDL error: %s\n", SDL_GetError());
	}

	SDL_SetTextureBlendMode(sdlTexture_, BLEND_MODE_);
	SDL_SetTextureAlphaMod(sdlTexture_, alpha_);
	SDL_FreeSurface(s);
}

