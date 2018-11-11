#ifndef MAP_H
#define MAP_H

#include <string>
#include "graphics.h"
#include <vector>
#include "Tile.h"
#include "Vector2.h"
#include "hitBox.h"

using namespace std;

class Map {
public:
	Map();
	Map(string fileNameMap, string fileNameTile, int tileSheetHeight, int tileSheetWidth, Graphics &graphics);
	~Map();

	vector <Direction> checkCollisions(HitBox box);

	bool updateOffset(float mX, float mY, Vector2 resolution, Vector2 playerOffset); //scroll the map when the player moves
	void draw(Graphics &graphics);
private:
	string _mapName;
	Vector2 _size; //size of the map
	Vector2 _tileSize; //size of each tile
	Vector2 _tileSheetSize;

	vector<HitBox> _hitBoxes;
	
	float _mapOffsetX; //position of all the tiles for screen scrolling
	float _mapOffsetY;

	vector<Tile> _tiles;
	SDL_Texture* _tileset;
	int _tilesetFirstGid;

	void loadMap(Graphics &graphics);
	void test();
};

#endif