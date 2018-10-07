#include "slime.h"

Slime::Slime() {}

Slime::Slime(int x, int y, int posX, int posY, int height, int width, string path, Graphics &graphics) :
	Enemy(x, y, posX, posY, height, width, path, graphics) {

	this->_x = x;
	this->_y = y;
	this->_sprite = Sprite(this->_x, this->_y, width, height, posX, posY, path, graphics);
	this->_hitBox = HitBox(x, y, width * 2, height * 2);

	this->_direction = FORWARD;
}

Slime::~Slime() {}

void Slime::AI() {
	this->_y += 0.1f;
}

void Slime::draw(Graphics &graphics) {
	this->_sprite.draw(this->_x, this->_y, graphics);
	this->_hitBox.draw(graphics);

}

void Slime::update(Uint32 elapsedTime) {
	AI();
}