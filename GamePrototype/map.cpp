#include "map.h"
#include "tinyxml2.h"
#include <sstream>
#include <SDL.h>
#include <iostream>

using namespace tinyxml2;

Map::Map() {}

Map::Map(string fileNameMap, string fileNameTile, int tileSheetHeight, int tileSheetWidth, Graphics &graphics) {
	this->_mapName = fileNameMap;
	this->_tileset = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(fileNameTile));
	this->_tileSheetSize = Vector2(tileSheetWidth, tileSheetHeight);
	this->_mapOffset = Vector2(0, 0);
	this->loadMap(graphics);
}

Map::~Map() {}

void Map::loadMap(Graphics &graphics) {
	//Parse the .tmx file
	XMLDocument doc;
	doc.LoadFile(this->_mapName.c_str());
	XMLElement* mapNode = doc.FirstChildElement("map");

	//Get the width and height of the map
	int width;
	int height;
	mapNode->QueryIntAttribute("width", &width);
	mapNode->QueryIntAttribute("height", &height);
	this->_size = Vector2(width, height);

	//Get the width and the height of the tiles
	int tileWidth, tileHeight;
	mapNode->QueryIntAttribute("tilewidth", &tileWidth);
	mapNode->QueryIntAttribute("tileheight", &tileHeight);
	this->_tileSize = Vector2(tileWidth, tileHeight);

	//Get the first gid
	XMLElement* tileset = mapNode->FirstChildElement("tileset");
	int firstgid;
	tileset->QueryIntAttribute("firstgid", &firstgid);
	this->_tilesetFirstGid = firstgid;

	//load the layers
	XMLElement* layer = mapNode->FirstChildElement("layer");
	while (layer) {
		XMLElement* data = layer->FirstChildElement("data");
		while (data) {
			XMLElement* tile = data->FirstChildElement("tile");
			int xpos = 0;
			int ypos = 0;
			while (tile) {
				int gid = tile->IntAttribute("gid");
				if (gid != 0) {
					//calculate the position on the tilesheet
					int tx = gid % this->_tileSheetSize.x;
					if (tx == 0) {
						tx = this->_tileSheetSize.x;
					}
					int ty;
					if (gid < this->_tileSheetSize.x) {
						ty = 1;
					} else {
						ty = gid / this->_tileSheetSize.y;
					}
					Vector2 tilePosition = Vector2((tx)*tileWidth, (ty)*tileHeight);

					Vector2 screenPosition = Vector2(xpos*tileWidth, ypos*tileHeight);
					Tile newTile = Tile(this->_tileset, this->_tileSize, tilePosition, screenPosition);
					this->_tiles.push_back(newTile);
					
				}
				if (xpos+1 == this->_size.x) {
					xpos = 0;
					ypos++;
				} else {
					xpos++;
				}
				tile = tile->NextSiblingElement("tile");
			}
			data = data->NextSiblingElement("data");
		}
		layer = layer->NextSiblingElement("layer");
	}
}

void Map::draw(Graphics &graphics) {
	for (int i = 0; i < this->_tiles.size(); i++) {
		this->_tiles.at(i).draw(this->_mapOffset, graphics);
	}
}

void Map::updateOffset(int changeX, int changeY) {
	this->_mapOffset.x += changeX;
	this->_mapOffset.y += changeY;
}

void Map::test() {
	XMLDocument doc;
	doc.LoadFile(this->_mapName.c_str());
	XMLElement* mapNode = doc.FirstChildElement("map");

	//load the layers
	XMLElement* layer = mapNode->FirstChildElement("layer");
	while (layer) {
		XMLElement* data = layer->FirstChildElement("data");
		while (data) {
			XMLElement* tile = data->FirstChildElement("tile");
			while (tile) {
				cout << tile->IntAttribute("gid") << endl;
				tile = tile->NextSiblingElement("tile");
			}
			data = data->NextSiblingElement("data");
		}
		layer = layer->NextSiblingElement("layer");
	}
}