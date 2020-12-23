#include "texture.h"

Texture::~Texture() {
	if (texture_) {
		SDL_DestroyTexture(texture_);
		texture_ = nullptr;
	}
}

void Texture::init(SDL_Texture* t, Window* w, int x, int y) {
	texture_ = t;
	window_ = w;

	rect_.x = x;
	rect_.y = y;
	SDL_QueryTexture(texture_, nullptr, nullptr, &rect_.w, &rect_.h);

	if (texture_ && window_) {
		initialized_ = true;
	}
}

void Texture::paint() {
	if (!initialized_) {
		return;
	}

	window_->paint(texture_, rect_, angle_, clip_, flip_, alpha_);
}

void Texture::setPosition(int x, int y) {
	rect_.x = x;
	rect_.y = y;
}

void Texture::setDimensions(int w, int h) {
	rect_.w = w;
	rect_.h = h;
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

void Texture::setAlpha(int a) {
	alpha_ = a;
}

void Texture::setFlip(SDL_RendererFlip f) {
	flip_ = f;
}