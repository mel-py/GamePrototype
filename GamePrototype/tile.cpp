#include "tile.h"
#include <iostream>

Tile::Tile() {}

Tile::Tile(SDL_Texture* tileSet, Vector2 size, Vector2 tilesetPosition, Vector2 position) {
	this->_tileset = tileSet;
	this->_size = size;
	this->_tilesetPosition = tilesetPosition;
	this->_position = position;

	this->_sourceRect.x = this->_tilesetPosition.x; 
	this->_sourceRect.y = this->_tilesetPosition.y;
	this->_sourceRect.w = this->_size.x;
	this->_sourceRect.h = this->_size.y;
}

Tile::~Tile() {}

void Tile::draw(Graphics &graphics) {
	SDL_Rect destRect = { this->_position.x, this->_position.y, this->_size.x, this->_size.y };
	graphics.blitSurface( this->_tileset, &this->_sourceRect, &destRect );
}
