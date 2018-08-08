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

bool HitBox::checkCollision(HitBox box) {
	return false;
}

void HitBox::draw(Graphics &graphics) {
	SDL_Rect rectToDraw = {this->_pos.x + this->_offset.x, this->_pos.y + this->_offset.y, this->_dimensions.x, this->_dimensions.y};
	SDL_SetRenderDrawColor(graphics.getRenderer(), 255, 0, 0, 0);
	SDL_RenderDrawRect(graphics.getRenderer(), &rectToDraw);
}
