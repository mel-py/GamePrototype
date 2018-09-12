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

bool HitBox::checkCollision(HitBox box) {
	Vector2 size2 = box.getSize();
	Vector2 pos2 = box.getPosition();
	Vector2 offset2 = box.getOffset();

	if (this->_pos.x + this->_dimensions.x + this->_offset.x < pos2.x + offset2.x) {
		return false; //box 1 is to the left of box 2
	}
	if (this->_pos.x + this->_offset.x > pos2.x + size2.x + offset2.x) {
		return false; //box 1 is to the right of box 2
	}
	if (this->_pos.y + this->_dimensions.y + this->_offset.y < pos2.y + offset2.y) {
		return false; //box 1 is above box 2
	}
	if (this->_pos.y + this->_offset.y > pos2.y + size2.y + offset2.y) {
		return false; //box 1 is below box 2
	}
}

void HitBox::draw(Graphics &graphics) {
	SDL_Rect rectToDraw = {this->_pos.x + this->_offset.x, this->_pos.y + this->_offset.y, this->_dimensions.x, this->_dimensions.y};
	SDL_SetRenderDrawColor(graphics.getRenderer(), 255, 0, 0, 0);
	SDL_RenderDrawRect(graphics.getRenderer(), &rectToDraw);
}
