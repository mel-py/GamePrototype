#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include <SDL_image.h>

class Graphics {
public:
	Graphics();
	Graphics(int screenWidth, int screenHeight);
	~Graphics();

	SDL_Texture* loadTexture(const char* path);

	void blitSurface(SDL_Texture* texture);
	void flip();
	void clear();
private:
	int _screenWidth;
	int _screenHeight;

	SDL_Window* _window;
	SDL_Surface* _screenSurface;
	SDL_Renderer* _renderer;
};

#endif