#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include "graphics.h"
#include <string>

using namespace std;

class Sprite {
public:
	Sprite();
	//x and y are the current position of the sprite on the screen
	//source x and source y are the position on the sprite sheet of the sprite
	Sprite(int x, int y, int width, int height, int sourceX, int sourceY, const string path, Graphics &graphics);
	~Sprite();

	void draw(int x, int y, Graphics &graphics);
protected:
	SDL_Texture* _sprite;
	SDL_Rect _sourceRect;

	int _x, _y;
};

#endif