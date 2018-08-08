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
	this->_mapOffsetX = 0;
	this->_mapOffsetY = 0;
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

	//get the hitboxes for walls and stuff
	XMLElement* objectGroup = mapNode->FirstChildElement("objectgroup");
	while (objectGroup) {
		XMLElement* object = objectGroup->FirstChildElement("object");
		while (object) {
			float x = object->IntAttribute("x");
			float y = object->IntAttribute("y");
			int width = object->IntAttribute("width");
			int height = object->IntAttribute("height");
			this->_hitBoxes.push_back(HitBox(x, y, width, height));
			object = object->NextSiblingElement("object");
		}
		objectGroup = objectGroup->NextSiblingElement("objectgroup");
	}
}

void Map::draw(Graphics &graphics) {
	for (int i = 0; i < this->_tiles.size(); i++) {
		this->_tiles.at(i).draw(this->_mapOffsetX, this->_mapOffsetY, graphics);
	}
	for (int i = 0; i < this->_hitBoxes.size(); i++) {
		this->_hitBoxes.at(i).draw(graphics);
	}
}

//update the offset from screen scrolling
//we want to stop screen scrolling when the edges of the map are reached
//return false if the offset can't be updated
bool Map::updateOffset(float mX, float mY, Vector2 resolution, Vector2 playerOffset) {
	//check if the edge of the screen is reached in the x direction
	if (mX != 0) {
		if (playerOffset.x != resolution.x / 2) {
			return false;
		}
		if (0 >= this->_mapOffsetX) {
			if (((this->_size.x * this->_tileSize.x) - resolution.x) * -1 <= this->_mapOffsetX) {
				this->_mapOffsetX += mX;
			} else if (mX > 0) { // unstick from the side
				this->_mapOffsetX += mX;
			} else {
				return false;
			}
		} else if (mX < 0) { //unstick again
			this->_mapOffsetX += mX;
		} else {
			return false;
		}
	}

	//check in the y direction
	if (mY != 0) {
		if (playerOffset.y != resolution.y / 2) {
			return false;
		}
		if (0 >= this->_mapOffsetY) {
			if (((this->_size.y * this->_tileSize.y) - resolution.y) * -1 <= this->_mapOffsetY) {
				this->_mapOffsetY += mY;
			} else if (mY > 0) { // unstick from the side
				this->_mapOffsetY += mY;
			} else {
				return false;
			}
		} else if (mY < 0) { //unstick again
			this->_mapOffsetY += mY;
		} else {
			return false;
		}
	}

	//should only be called if false is not returned
	for (int i = 0; i < this->_hitBoxes.size(); i++) {
		this->_hitBoxes.at(i).moveBoxOffset(this->_mapOffsetX, this->_mapOffsetY);
	}
	return true;
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