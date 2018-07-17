#include "sprite.h"
#include <stdio.h>

Sprite::Sprite() {}

Sprite::Sprite(int x, int y, int width, int height, int sourceX, int sourceY, const string path, Graphics &graphics) {
	this->_x = x;
	this->_y = y;

	this->_sourceRect.h = height;
	this->_sourceRect.w = width;
	this->_sourceRect.x = sourceX;
	this->_sourceRect.y = sourceY;

	this->_sprite = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(path));
	if (this->_sprite == NULL) {
		printf("Unable to load image. SDL_Error: %s\n", SDL_GetError());
	}
}

Sprite::~Sprite() {
	//SDL_FreeSurface(this->_sprite);
}

void Sprite::draw(int x, int y, Graphics &graphics) {
	SDL_Rect destRect = { x, y, this->_sourceRect.w * 2, this->_sourceRect.h * 2 };
	graphics.blitSurface(this->_sprite, &this->_sourceRect, &destRect);
}