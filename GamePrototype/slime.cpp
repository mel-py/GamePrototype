#include "slime.h"
#include <stdlib.h>
#include <time.h>

Slime::Slime() {}

Slime::Slime(int x, int y, int posX, int posY, int height, int width, string path, Graphics &graphics) :
	Enemy(x, y, posX, posY, height, width, path, graphics) {

	this->_x = x;
	this->_y = y;
	this->_sprite = Sprite(this->_x, this->_y, width, height, posX, posY, path, graphics);
	this->_hitBox = HitBox(x, y, width * 2, height * 2);

	//randomize the direction
	srand(time(NULL));
	int direc = rand() % 1 + 4;
	if (direc == 1) {
		this->_direction = FORWARD;
	} else if (direc == 2) {
		this->_direction = BACKWARD;
	} else if (direc == 3) {
		this->_direction = LEFT;
	} else if (direc == 4) {
		this->_direction = RIGHT;
	}
	this->_health = 10;
}

Slime::~Slime() {}

void Slime::AI() {
	if (this->_direction == FORWARD) {
		this->_y += 0.05f;
	} else if (this->_direction == BACKWARD) {
		this->_y -= 0.05f;
	} else if (this->_direction == RIGHT) {
		this->_x += 0.05f;
	} else if (this->_direction == LEFT) {
		this->_x -= 0.05f;
	}
	this->_hitBox.moveBox(this->_x, this->_y);
}

void Slime::handleCollision() {
	if (this->_direction == FORWARD) {
		this->_direction = BACKWARD;
	} else if (this->_direction == BACKWARD) {
		this->_direction = FORWARD;
	} else if (this->_direction == RIGHT) {
		this->_direction = LEFT;
	} else if (this->_direction == LEFT) {
		this->_direction = RIGHT;
	}
}

void Slime::updateHealth(signed int amntToUpdate) {
	this->_health += amntToUpdate;
	if (this->_health <= 0) {
		this->_x = -100;
		this->_y = -100;
	}
}

void Slime::updateOffset(float mX, float mY) {
	this->_x += mX;
	this->_y += mY;
	this->_hitBox.moveBox(this->_x, this->_y);
}

HitBox Slime::getHitBox() {
	return this->_hitBox;
}

void Slime::draw(Graphics &graphics) {
	this->_sprite.draw(this->_x, this->_y, graphics);
	this->_hitBox.draw(graphics);
}

void Slime::update(Uint32 elapsedTime) {
	AI();
}