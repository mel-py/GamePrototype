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

	this->_hitBox = HitBox(x, y, 32, 32);

	this->_direction = FORWARD;
}

Player::~Player() {}

void Player::movePlayer(Direction direction) {
		this->_sprites[this->_direction].playAnimation();
		if (direction == BACKWARD) {
			this->_direction = BACKWARD;
		} else if (direction == FORWARD) {
			this->_direction = FORWARD;
		} else if (direction == LEFT) {
			this->_direction = LEFT;
		} else if (direction == RIGHT) {
			this->_direction = RIGHT;
		}
}

void Player::updatePlayerOffset(float mX, float mY) {
	this->_x += mX;
	this->_y += mY;
	this->_hitBox.moveBox(this->_x, this->_y);
}

Vector2 Player::getPlayerOffset() {
	return Vector2(this->_x, this->_y);
}

void Player::stopMoving() {
	this->_sprites[this->_direction].stopAnimation();
}

void Player::update(Uint32 elapsedTime) {
	this->_sprites[this->_direction].update(elapsedTime);
}

void Player::draw(Graphics &graphics) {
	this->_sprites[this->_direction].draw(this->_x, this->_y, graphics);
	this->_hitBox.draw(graphics);
}