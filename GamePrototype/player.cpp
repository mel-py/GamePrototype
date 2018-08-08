#include "player.h"

const float ACCELERATION = 0.01f; //speed in which the character accelerates when movement starts
const float MAX_SPEED = 0.05f; //maximum speed the character can reach

Player::Player() {}

Player::Player(int x, int y, string path, Graphics &graphics) {
	this->_x = x;
	this->_y = y;

	this->_sprites.insert(pair<Direction, AnimatedSprite>(BACKWARD, AnimatedSprite(x, y, 16, 16, 0, 0, path, graphics, 4, 100.0f)));
	this->_sprites.insert(pair<Direction, AnimatedSprite>(RIGHT, AnimatedSprite(x, y, 16, 16, 0, 16, path, graphics, 4, 100.0f)));
	this->_sprites.insert(pair<Direction, AnimatedSprite>(FORWARD, AnimatedSprite(x, y, 16, 16, 0, 32, path, graphics, 4, 100.0f)));
	this->_sprites.insert(pair<Direction, AnimatedSprite>(LEFT, AnimatedSprite(x, y, 16, 16, 0, 48, path, graphics, 4, 100.0f)));

	this->_direction = FORWARD;
}

Player::~Player() {}

void Player::movePlayer(string direction) {
		this->_sprites[this->_direction].playAnimation();
		/*if (this->_speed < MAX_SPEED) {
			this->_speed += ACCELERATION;
		}*/
		if (direction == "backwards") {
			this->_direction = BACKWARD;
			//this->_y -= this->_speed;
		} else if (direction == "forwards") {
			this->_direction = FORWARD;
			//this->_y += this->_speed;
		} else if (direction == "left") {
			this->_direction = LEFT;
			//this->_x -= this->_speed;
		} else if (direction == "right") {
			this->_direction = RIGHT;
			//this->_x += this->_speed;
		}
}

void Player::updatePlayerOffset(float mX, float mY) {
	this->_x += mX;
	this->_y += mY;
}

Vector2 Player::getPlayerOffset() {
	return Vector2(this->_x, this->_y);
}

void Player::stopMoving() {
	this->_sprites[this->_direction].stopAnimation();
	this->_speed = 0;
}

void Player::update(Uint32 elapsedTime) {
	this->_sprites[this->_direction].update(elapsedTime);
}

void Player::draw(Graphics &graphics) {
	this->_sprites[this->_direction].draw(this->_x, this->_y, graphics);
}