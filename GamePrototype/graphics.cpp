#include "graphics.h"
#include <iostream>

Graphics::Graphics() {
	this->_screenWidth = 420;
	this->_screenHeight = 680;

	this->_window = SDL_CreateWindow("Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 420, 680, SDL_WINDOW_SHOWN);
	if (this->_window == NULL) {
		cout << "Window could not be initialized, " << SDL_GetError() << endl;
	} else {
		this->_screenSurface = SDL_GetWindowSurface(this->_window);

		SDL_FillRect(this->_screenSurface, NULL, SDL_MapRGB(this->_screenSurface->format, 0xFF, 0xFF, 0xFF));

		SDL_UpdateWindowSurface(this->_window);
	}

	this->_renderer = SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_ACCELERATED);
	if (this->_renderer == NULL) {
		cout << "Renerer could not be created " << SDL_GetError() << endl;
	}
}

Graphics::Graphics(int sWidth, int sHeight) {
	this->_screenHeight = sHeight;
	this->_screenWidth = sWidth;

	this->_window = SDL_CreateWindow("Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, sWidth, sHeight, SDL_WINDOW_SHOWN);
	if (this->_window == NULL) {
		cout << "Window could not be initialized, " << SDL_GetError() << endl;
	} else {
		this->_screenSurface = SDL_GetWindowSurface(this->_window);

		SDL_FillRect(this->_screenSurface, NULL, SDL_MapRGB(this->_screenSurface->format, 0xFF, 0xFF, 0xFF));

		SDL_UpdateWindowSurface(this->_window);
	}

	this->_renderer = SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_ACCELERATED);
	if (this->_renderer == NULL) {
		cout << "Renerer could not be created " << SDL_GetError() << endl;
	}
}

Graphics::~Graphics() {
	SDL_DestroyWindow(this->_window);
	SDL_DestroyRenderer(this->_renderer);
}

SDL_Surface* Graphics::loadImage(const string path) {
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		cout << "Unable to load image. SDL_image Error: " <<  IMG_GetError() << endl;
	}

	return loadedSurface;
}

Vector2 Graphics::getResolution() {
	return Vector2(this->_screenWidth, this->_screenHeight);
}

SDL_Renderer* Graphics::getRenderer() {
	return this->_renderer;
}

void Graphics::blitSurface(SDL_Texture* texture, SDL_Rect* source, SDL_Rect* dest) {
	SDL_RenderCopy(this->_renderer, texture, source, dest);
}

void Graphics::flip() {
	SDL_RenderPresent(this->_renderer);
}

void Graphics::clear() {
	SDL_RenderClear(this->_renderer);
}