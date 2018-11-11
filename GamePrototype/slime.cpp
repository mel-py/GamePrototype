#include "slime.h"

Slime::Slime() {}

Slime::Slime(int x, int y, int posX, int posY, int height, int width, string path, Graphics &graphics) :
	Enemy(x, y, posX, posY, height, width, path, graphics) {

	this->_x = x;
	this->_y = y;
	this->_sprite = Sprite(this->_x, this->_y, width, height, posX, posY, path, graphics);
	this->_hitBox = HitBox(x, y, width * 2, height * 2);

	this->_direction = FORWARD;
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

void Slime::handleCollision(Direction collision) {
	/*
	*We are checking what side with the tile the enemy is colliding with i.e. if moving to the left we will collide on the right side of the tile
	*Since we want the enemy to move in the opposite direction of the collision we would then move to the right in this example
	*So the direction we are switching to is the same side as we are colliding for
	*/
	this->_direction = collision;
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