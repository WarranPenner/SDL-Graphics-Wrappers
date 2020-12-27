#pragma once
#include <SDL.h>
#include <utility>

class Viewport {
public:
	void init(int w, int h, int originX = 0, int originY = 0);
	void initWithTarget(int w, int h, const int* tx, const int* ty);
	void move(int x, int y);
	void setToFollow(int* x, int* y);
	SDL_Rect getRect();
	bool isInitialized();
private:
	SDL_Rect vpRect_ = {0, 0, 0, 0};
	const int* targetX_ = nullptr;
	const int* targetY_ = nullptr;
	int		targAllowanceLeft_ = 80,		targAllowanceRight_ = 0;
	//	These variables define an area relative to the viewport's center where
	//	the target can move without triggering viewport movement.
	bool initialized_ = false;

	void focusOnTarget();
	std::pair<int, int> getHorizontalBoundaries();
};