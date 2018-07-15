#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include "graphics.h"

using namespace std;

class Sprite {
public:
	Sprite();
	Sprite(int x, int y, const char* path, Graphics &graphics);
	~Sprite();

	void draw(Graphics &graphics);
private:
	SDL_Texture* _sprite;
	int _x, _y;
};

#endif