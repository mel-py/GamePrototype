#include "hitBox.h"
#include <iostream>

using namespace std;

HitBox::HitBox() {
	this->_pos = Vector2(0, 0);
	this->_dimensions = Vector2(0, 0);
	this->_offset = Vector2(0, 0);
}

HitBox::HitBox(float x, float y, int width, int height) {
	this->_pos = Vector2(x, y);
	this->_dimensions = Vector2(width, height);
	this->_offset = Vector2(0, 0);
}

HitBox::~HitBox() {}

void HitBox::moveBox(float mX, float mY) {
	this->_pos.x = mX;
	this->_pos.y = mY;
}

void HitBox::moveBoxOffset(float offsetX, float offsetY) {
	this->_offset.x = offsetX;
	this->_offset.y = offsetY;
}

Vector2 HitBox::getPosition() {
	return this->_pos;
}

Vector2 HitBox::getSize() {
	return this->_dimensions;
}

Vector2 HitBox::getOffset() {
	return this->_offset;
}

Direction HitBox::checkCollision(HitBox box) {
	Vector2 size2 = box.getSize();
	Vector2 pos2 = box.getPosition();
	Vector2 offset2 = box.getOffset();

	//check is a collision is occuring
	if (this->_pos.x + this->_dimensions.x + this->_offset.x < pos2.x + offset2.x) {
		return NONE; //box 1 is to the left of box 2
	}
	if (this->_pos.x + this->_offset.x > pos2.x + size2.x + offset2.x) {
		return NONE; //box 1 is to the right of box 2
	}
	if (this->_pos.y + this->_dimensions.y + this->_offset.y < pos2.y + offset2.y) {
		return NONE; //box 1 is above box 2
	}
	if (this->_pos.y + this->_offset.y > pos2.y + size2.y + offset2.y) {
		return NONE; //box 1 is below box 2
	}

	//a collision is occuring, check what side its occuring on
	Vector2 boxPos = box.getPosition();
	Vector2 boxSize = box.getSize();
	Vector2 boxOffset = box.getOffset();
	//Box1 Right - Box2 Left
	int amntRight = (this->_dimensions.x + this->_offset.x + this->_pos.x) - (boxPos.x + boxOffset.x);
	//Box2 Left - Box1 Left
	int amntLeft = (boxPos.x + boxOffset.x) - (this->_pos.x + this->_offset.x);
	//Box2 bottom - Box1 Top
	int amntTop = (boxPos.y + boxOffset.y + boxSize.y) - (this->_pos.y + this->_offset.y);
	//Box1 bottom - Box2 Top
	int amntBottom = (this->_dimensions.y + this->_pos.y + this->_offset.y) - (boxPos.y + boxOffset.y);

	int vals[4] = { abs(amntRight), abs(amntLeft), abs(amntBottom), abs(amntTop) };
	int lowest = vals[0];
	for (int i = 1; i < 4; i++) {
		if (vals[i] < lowest) {
			lowest = vals[i];
		}
	}

	return
		lowest == abs(amntRight) ? Direction::RIGHT :
		lowest == abs(amntLeft) ? Direction::LEFT :
		lowest == abs(amntBottom) ? Direction::BACKWARD :
		lowest == abs(amntTop) ? Direction::FORWARD :
		Direction::NONE;
}

void HitBox::draw(Graphics &graphics) {
	SDL_Rect rectToDraw = {this->_pos.x + this->_offset.x, this->_pos.y + this->_offset.y, this->_dimensions.x, this->_dimensions.y};
	SDL_SetRenderDrawColor(graphics.getRenderer(), 255, 0, 0, 0);
	SDL_RenderDrawRect(graphics.getRenderer(), &rectToDraw);
}