#include "viewport.h"


void Viewport::init(int w, int h, int originX, int originY) {
	vpRect_.x = originX;
	vpRect_.y = originY;
	vpRect_.w = w;
	vpRect_.h = h;
	initialized_ = true;
}

void Viewport::initWithTarget(int w, int h, const int* tx, const int* ty) {
	if (!tx || !ty) {
		printf("ERROR: Target position pointers sent to Viewport are null!\n");
		return;
	}

	targetX_ = tx;
	targetY_ = ty;
	focusOnTarget();

	vpRect_.w = w;
	vpRect_.h = h;
	initialized_ = true;
}

void Viewport::move(int x, int y) {
	vpRect_.x = x;
	vpRect_.y = y;
}

void Viewport::setToFollow(int* x, int* y) {
	targetX_ = x;
	targetY_ = y;
}

SDL_Rect Viewport::getRect() {
	if (targetX_ || targetY_) {
		focusOnTarget();
	}

	return vpRect_;
}

bool Viewport::isInitialized() {
	return initialized_;
}

void Viewport::focusOnTarget() {
	std::pair<int, int> targBoundaries = getHorizontalBoundaries();

	if (*targetX_ < targBoundaries.first) {
		vpRect_.x -= targBoundaries.first - *targetX_;
	} else if (*targetX_ > targBoundaries.second) {
		vpRect_.x += *targetX_ - targBoundaries.second;
	}
}

std::pair<int, int> Viewport::getHorizontalBoundaries() {
	return {vpRect_.x + (vpRect_.w / 2) - targAllowanceLeft_,
			vpRect_.x + (vpRect_.w / 2) + targAllowanceRight_};
}