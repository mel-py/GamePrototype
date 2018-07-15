#include "sprite.h"
#include <stdio.h>

Sprite::Sprite() {}

Sprite::Sprite(int x, int y, const char* path, Graphics &graphics) {
	this->_x = x;
	this->_y = y;

	this->_sprite = graphics.loadTexture(path);
	if (this->_sprite == NULL) {
		printf("Unable to load image. SDL_Error: %s\n", SDL_GetError());
	}
}

Sprite::~Sprite() {
	//SDL_FreeSurface(this->_spriteSurface);
}

void Sprite::draw(Graphics &graphics) {
	graphics.blitSurface(this->_sprite);
}