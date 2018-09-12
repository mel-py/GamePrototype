#include "enemy.h"
#include <iostream>

Enemy::Enemy() {}

Enemy::Enemy(int x, int y, int posX, int posY, int height, int width, string path, Graphics &graphics) {
	this->_x = x;
	this->_y = y;

	this->_sprite = Sprite(this->_x, this->_y, width, height, posX, posY, path, graphics);
}

Enemy::~Enemy() {}

void Enemy::AI() {

}

void Enemy::draw(Graphics &graphics) {
	//cout << "drawing..." << endl;
	this->_sprite.draw(this->_x, this->_y, graphics);
}

void Enemy::update(Uint32 elapsedTime) {
	AI();
}