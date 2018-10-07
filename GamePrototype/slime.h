#pragma once

#ifndef SLIME_H
#define SLIME_H

#include "enemy.h"
#include "hitBox.h"
#include "sprite.h"

class Slime : public Enemy {
public:
	Slime();
	Slime(int x, int y, int posX, int posY, int height, int width, string path, Graphics &graphics);
	~Slime();

	void AI();
	void move();

	void draw(Graphics &graphics);
	void update(Uint32 elapsedTime);
private:

	Direction _direction;

	Sprite _sprite;
	HitBox _hitBox;

	float _x, _y;
};

#endif