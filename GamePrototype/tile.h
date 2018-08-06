#ifndef TILE_H
#define TILE_H

#include <SDL.h>
#include "Vector2.h"
#include "graphics.h"

class Tile {
public:
	Tile();
	Tile(SDL_Texture* tileset, Vector2 size, Vector2 tilesetPosition, Vector2 position);
	~Tile();

	void draw(Graphics &graphics);
private:
	//position is the position of the tile on the screen
	//tilesetPosition is the position of the tile on the tileset
	SDL_Texture* _tileset;
	SDL_Rect _sourceRect;
	Vector2 _size;
	Vector2 _tilesetPosition;
	Vector2 _position;
};

#endif