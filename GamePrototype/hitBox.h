#ifndef HITBOX_H
#define HITBOX_H

#include "Vector2.h"
#include "graphics.h"
#include <SDL.h>
#include "globals.h"

class HitBox {
public:
	HitBox();
	HitBox(float x, float y, int width, int height);
	~HitBox();

	void moveBox(float mX, float mY);
	void moveBoxOffset(float offsetX, float offsetY);

	Vector2 getSize();
	Vector2 getPosition();
	Vector2 getOffset();

	bool checkCollision(HitBox box);

	void draw(Graphics &graphics);
private:
	Vector2 _pos;
	Vector2 _dimensions;
	Vector2 _offset;
};

#endif