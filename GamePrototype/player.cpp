#include "player.h"
#include <iostream>

using namespace std;

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
	this->_sprites.insert(pair<Direction, AnimatedSprite>(ATTACK_BACKWARD, AnimatedSprite(x, y, 16, 16, 0, 64, path, graphics, 1, 100.0f)));
	this->_sprites.insert(pair<Direction, AnimatedSprite>(ATTACK_RIGHT, AnimatedSprite(x, y, 16, 16, 16, 64, path, graphics, 1, 100.0f)));
	this->_sprites.insert(pair<Direction, AnimatedSprite>(ATTACK_FORWARD, AnimatedSprite(x, y, 16, 16, 32, 64, path, graphics, 1, 100.0f)));
	this->_sprites.insert(pair<Direction, AnimatedSprite>(ATTACK_LEFT, AnimatedSprite(x, y, 16, 16, 48, 64, path, graphics, 1, 100.0f)));

	this->_hitBox = HitBox(x, y, 32, 32);

	this->_directions[0] = FORWARD;
	this->_directions[1] = NONE;

	this->_health = 100;
	this->_energy = 100;

	this->_isAttacking = false;
}

Player::~Player() {}

void Player::movePlayer(Direction direction) {
	this->_sprites[this->_directions[0]].playAnimation();
	if (this->_directionIndex < 2) {
		this->_directions[this->_directionIndex] = direction;
		this->_directionIndex++;
	}	
}

void Player::attack() {
	if (!this->_isAttacking) {
		if (this->_directions[0] == LEFT) {
			this->_directions[0] = ATTACK_LEFT;
		} else if (this->_directions[0] == RIGHT) {
			this->_directions[0] = ATTACK_RIGHT;
		} else if (this->_directions[0] == FORWARD) {
			this->_directions[0] = ATTACK_FORWARD;
		} else if (this->_directions[0] == BACKWARD) {
			this->_directions[0] = ATTACK_BACKWARD;
		}
		this->_isAttacking = true;
	}
}

void Player::stopAttacking() {
	if (this->_isAttacking) {
		if (this->_directions[0] == ATTACK_LEFT) {
			this->_directions[0] = LEFT;
		} else if (this->_directions[0] == ATTACK_RIGHT) {
			this->_directions[0] = RIGHT;
		} else if (this->_directions[0] == ATTACK_FORWARD) {
			this->_directions[0] = FORWARD;
		} else if (this->_directions[0] == ATTACK_BACKWARD) {
			this->_directions[0] = BACKWARD;
		}
		this->_isAttacking = false;
	}
}

bool Player::isAttacking() {
	return this->_isAttacking;
}

void Player::beginNewFrame() {
	this->_directionIndex = 0;
	this->_directions[1] = NONE;
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
	this->_sprites[this->_directions[0]].stopAnimation();
}

HitBox Player::getHitBox() {
	return this->_hitBox;
}

Direction* Player::getDirection() {
	return this->_directions;
}

void Player::updateHealth(signed int amountToAdd) {
	this->_health += amountToAdd;
}

void Player::update(Uint32 elapsedTime) {
	if (this->_isAttacking && elapsedTime % 200 == 0) {
		stopAttacking();
	}
	this->_sprites[this->_directions[0]].update(elapsedTime);
}

void Player::draw(Graphics &graphics) {
	this->_sprites[this->_directions[0]].draw(this->_x, this->_y, graphics);
	this->_hitBox.draw(graphics);

	//draw the health bar
	SDL_Rect rectToDraw = { 75, 600, this->_health, 25 };
	SDL_SetRenderDrawColor(graphics.getRenderer(), 255, 0, 0, 0);
	SDL_RenderFillRect(graphics.getRenderer(), &rectToDraw);
	SDL_RenderDrawRect(graphics.getRenderer(), &rectToDraw);

	//energy bar
	rectToDraw = { 275, 600, this->_energy, 25 };
	SDL_SetRenderDrawColor(graphics.getRenderer(), 0, 220, 0, 60);
	SDL_RenderFillRect(graphics.getRenderer(), &rectToDraw);
	SDL_RenderDrawRect(graphics.getRenderer(), &rectToDraw);
}