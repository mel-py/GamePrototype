#include "spider.h"
#include <stdlib.h>
#include <iostream>
#include <time.h>

Spider::Spider() {}

Spider::Spider(int x, int y, int posX, int posY, int height, int width, string path, Graphics &graphics) :
	Enemy(x, y, posX, posY, height, width, path, graphics) {

	this->_x = x;
	this->_y = y;
	this->_sprite = Sprite(x, y, width, height, 0, 0, path, graphics);
	this->_hitBox = HitBox(x, y, width * 2, height * 2);

	this->_direction1 = RIGHT;
	this->_direction2 = FORWARD;
	this->_health = 20;
}

Spider::~Spider() {}

void Spider::AI(vector<HitBox> mapTiles) {
	if (this->_direction2 == FORWARD) {
		this->_y += 0.05f;
		if (checkCollision(mapTiles) == true) {
			this->_y -= 0.1f;
			this->_direction2 = BACKWARD;
		}
	} else if (this->_direction2 == BACKWARD) {
		this->_y -= 0.05f;
		if (checkCollision(mapTiles) == true) {
			this->_y += 0.1f;
			this->_direction2 = FORWARD;
		}
	} 
	if (this->_direction1 == RIGHT) {
		this->_x += 0.05f;
		if (checkCollision(mapTiles) == true) {
			this->_x -= 0.1f;
			this->_direction1 = LEFT;
		}
	} else if (this->_direction1 == LEFT) {
		this->_x -= 0.05f;
		if (checkCollision(mapTiles) == true) {
			this->_x += 0.1f;
			this->_direction1 = RIGHT;
		}
	}
	this->_hitBox.moveBox(this->_x, this->_y);
}

//return true if dead
bool Spider::updateHealth(signed int amntToUpdate) {
	this->_health += amntToUpdate;
	if (this->_health <= 0) {
		return true;
	}
	return false;
}

void Spider::updateOffset(float mX, float mY) {
	this->_x += mX;
	this->_y += mY;
	this->_hitBox.moveBox(this->_x, this->_y);
}

HitBox Spider::getHitBox() {
	return this->_hitBox;
}

void Spider::draw(Graphics &graphics) {
	this->_sprite.draw(this->_x, this->_y, graphics);
	this->_hitBox.draw(graphics);
}

void Spider::update(Uint32 elapsedTime, vector<HitBox> mapTiles) {
	AI(mapTiles);
}

bool Spider::checkCollision(vector<HitBox> mapTiles) {
	for (int i = 0; i < mapTiles.size(); i++) {
		if (mapTiles.at(i).checkCollision(this->_hitBox) == true) {
			return true;
		}
	}
	return false;
}