#include "enemy.h"
#include <iostream>

Enemy::Enemy() {}

Enemy::Enemy(int x, int y, int posX, int posY, int height, int width, string path, Graphics &graphics) {
	this->_x = x;
	this->_y = y;

	this->_sprite = Sprite(this->_x, this->_y, width, height, posX, posY, path, graphics);
}

Enemy::~Enemy() {}

void Enemy::AI() {}

void Enemy::updateOffset(float mX, float mY) {
	this->_x += mX;
	this->_y += mY;
}

void Enemy::draw(Graphics &graphics) {
	this->_sprite.draw(this->_x, this->_y, graphics);
}

void Enemy::update(Uint32 elapsedTime) {
	AI();
}

bool Enemy::checkCollision(vector<HitBox> mapTiles) {
	for (int i = 0; i < mapTiles.size(); i++) {
		if (mapTiles.at(i).checkCollision(this->_hitBox)) {
			return true;
		}
	}
	return false;
}