#include "text.h"

void Text::init(Window* w, std::string ttfPath, int size) {
	font_ = TTF_OpenFont(ttfPath.c_str(), size);
	if (!font_) {
		printf("ERROR: Font '%s' could not be loaded!\n", ttfPath.c_str());
		printf("SDL error: %s\n", TTF_GetError());
		return;
	}

	if (w) {
		window_ = w;
		initialized_ = true;
	}
}

void Text::write(std::string text, std::pair<int, int> pos) {
	if (text != text_) {
		text_ = text;
		createTexture();
	}
	
	rect_.x = pos.first;
	rect_.y = pos.second;
	Texture::paint();
}

void Text::setColor(SDL_Color c) {
	color_ = c;
}

void Text::setStyle(int ttfStyleBitmask) {
	// TTF style bitmask is composed of the following masks:
	//		- TTF_STYLE_BOLD
	//		- TTF_STYLE_ITALIC
	//		- TTF_STYLE_UNDERLINE
	//		- TTF_STYLE_STRIKETHROUGH
	TTF_SetFontStyle(font_, ttfStyleBitmask);
}

void Text::resetStyle() {
	TTF_SetFontStyle(font_, TTF_STYLE_NORMAL);
}

void Text::createTexture() {
	if (sdlTexture_) {
		SDL_DestroyTexture(sdlTexture_);
		sdlTexture_ = nullptr;
	}

	SDL_Surface* s = TTF_RenderText_Solid(font_, text_.c_str(),
		color_);
	sdlTexture_ = SDL_CreateTextureFromSurface(window_->getRenderer(), s);

	SDL_QueryTexture(sdlTexture_, nullptr, nullptr, &rect_.w, &rect_.h);
	clip_.w = rect_.w;
	clip_.h = rect_.h;
}