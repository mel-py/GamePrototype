#include "enemy.h"
#include <iostream>

Enemy::Enemy() {}

Enemy::Enemy(int x, int y, int posX, int posY, int height, int width, string path, Graphics &graphics) {
	this->_x = x;
	this->_y = y;

	this->_sprite = Sprite(this->_x, this->_y, width, height, posX, posY, path, graphics);
	this->_hitbox = HitBox(x, y, width * 2, height * 2);
}

Enemy::~Enemy() {}

void Enemy::AI() {

}

void Enemy::draw(Graphics &graphics) {
	//cout << "drawing..." << endl;
	this->_sprite.draw(this->_x, this->_y, graphics);
	this->_hitbox.draw(graphics);
}

void Enemy::update(Uint32 elapsedTime) {
	AI();
}