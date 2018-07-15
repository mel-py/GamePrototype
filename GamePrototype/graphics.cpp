#include "graphics.h"
#include <iostream>

using namespace std;

Graphics::Graphics() {
	this->_screenWidth = 480;
	this->_screenHeight = 640;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "SDL could not be initialized, " << SDL_GetError() << endl;
	}
	else {
		this->_window = SDL_CreateWindow("Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 480, 640, SDL_WINDOW_SHOWN);
		if (this->_window == NULL) {
			cout << "Window could not be initialized, " << SDL_GetError() << endl;
		}
		else {
			this->_screenSurface = SDL_GetWindowSurface(this->_window);

			SDL_FillRect(this->_screenSurface, NULL, SDL_MapRGB(this->_screenSurface->format, 0xFF, 0xFF, 0xFF));

			SDL_UpdateWindowSurface(this->_window);

			SDL_Delay(2000);
		}
	}

	this->_renderer = SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_ACCELERATED);
	if (this->_renderer == NULL) {
		cout << "Renerer could not be created " << SDL_GetError() << endl;
	}
}

Graphics::Graphics(int screenWidth, int screenHeight) {
	this->_screenWidth = screenWidth;
	this->_screenHeight = screenHeight;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "SDL could not be initialized, " << SDL_GetError() << endl;
	}
	else {
		this->_window = SDL_CreateWindow("Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->_screenWidth, this->_screenHeight, SDL_WINDOW_SHOWN);
		if (this->_window == NULL) {
			cout << "Window could not be initialized, " << SDL_GetError() << endl;
		}
		else {
			this->_screenSurface = SDL_GetWindowSurface(this->_window);

			SDL_FillRect(this->_screenSurface, NULL, SDL_MapRGB(this->_screenSurface->format, 0xFF, 0xFF, 0xFF));

			SDL_UpdateWindowSurface(this->_window);
		}
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

SDL_Texture* Graphics::loadTexture(const char* path) {
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path);
	if (loadedSurface == NULL) {
		printf("Unable to load image. SDL_image Error: %s\n", IMG_GetError());
	} else {
		newTexture = SDL_CreateTextureFromSurface(this->_renderer, loadedSurface);
		if (newTexture == NULL) {
			printf("Unable to create texture from. SDL Error: %s\n", SDL_GetError());
		}

		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

void Graphics::blitSurface(SDL_Texture* texture) {
	SDL_RenderCopy(this->_renderer, texture, NULL, NULL);
}

void Graphics::flip() {
	SDL_RenderPresent(this->_renderer);
}

void Graphics::clear() {
	SDL_RenderClear(this->_renderer);
}