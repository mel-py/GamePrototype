#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>

using namespace std;

class Graphics {
public:
	Graphics();
	Graphics(int screenWidth, int screenHeight);
	~Graphics();

	SDL_Surface* loadImage(const string path);
	SDL_Renderer* getRenderer();

	void blitSurface(SDL_Texture* texture, SDL_Rect* source, SDL_Rect* dest);
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