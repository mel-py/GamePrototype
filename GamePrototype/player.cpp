#include "player.h"

const float ACCELERATION = 0.5f; //speed in which the character accelerates when movement starts
const float MAX_SPEED = 6.0f; //maximum speed the character can reach

Player::Player() {}

Player::Player(int x, int y, string path, Graphics &graphics) {
	this->_x = x;
	this->_y = y;

	this->_sprites.insert(pair<Direction, AnimatedSprite>(BACKWARD, AnimatedSprite(x, y, 24, 32, 0, 0, "Sprites/link.png", graphics, 12, 500)));
	this->_sprites.insert(pair<Direction, AnimatedSprite>(RIGHT, AnimatedSprite(x, y, 24, 32, 0, 32, "Sprites/link.png", graphics, 12, 500)));
	this->_sprites.insert(pair<Direction, AnimatedSprite>(FORWARD, AnimatedSprite(x, y, 24, 32, 0, 64, "Sprites/link.png", graphics, 12, 500)));
	this->_sprites.insert(pair<Direction, AnimatedSprite>(LEFT, AnimatedSprite(x, y, 24, 32, 0, 96, "Sprites/link.png", graphics, 12, 500)));

	this->_direction = FORWARD;
}

Player::~Player() {}

void Player::movePlayer(string direction) {
		this->_sprites[this->_direction].playAnimation();
		if (this->_speed < MAX_SPEED) {
			this->_speed += ACCELERATION;
		}
		if (direction == "backwards") {
			this->_direction = BACKWARD;
			this->_y -= this->_speed;
		} else if (direction == "forwards") {
			this->_direction = FORWARD;
			this->_y += this->_speed;
		} else if (direction == "left") {
			this->_direction = LEFT;
			this->_x -= this->_speed;
		} else if (direction == "right") {
			this->_direction = RIGHT;
			this->_x += this->_speed;
		}
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