#ifndef HITBOX_H
#define HITBOX_H

#include "Vector2.h"
#include "graphics.h"
#include <SDL.h>

class HitBox {
public:
	HitBox();
	HitBox(float x, float y, int width, int height);
	~HitBox();

	void moveBox(float mX, float mY);
	void moveBoxOffset(float offsetX, float offsetY);

	bool checkCollision(HitBox box);

	void draw(Graphics &graphics);
private:
	Vector2 _pos;
	Vector2 _dimensions;
	Vector2 _offset;
};

#endif