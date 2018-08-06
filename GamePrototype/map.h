#ifndef MAP_H
#define MAP_H

#include <string>
#include "graphics.h"
#include <vector>
#include "Tile.h"
#include "Vector2.h"

using namespace std;

class Map {
public:
	Map();
	Map(string fileNameMap, string fileNameTile, int tileSheetHeight, int tileSheetWidth, Graphics &graphics);
	~Map();

	void updateOffset(int mX, int mY);
	void draw(Graphics &graphics);
private:
	string _mapName;
	Vector2 _size; //size of the map
	Vector2 _tileSize; //size of each tile
	Vector2 _tileSheetSize;
	
	Vector2 _mapOffset; //position of all the tiles for screen scrolling

	vector<Tile> _tiles;
	SDL_Texture* _tileset;
	int _tilesetFirstGid;

	void loadMap(Graphics &graphics);
	void test();
};

#endif