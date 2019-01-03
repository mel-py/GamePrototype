#pragma once
#pragma once

#ifndef SPIDER_H
#define SPIDER_H

#include "enemy.h"
#include "hitBox.h"
#include "sprite.h"

class Spider : public Enemy {
public:
	Spider();
	Spider(int x, int y, int posX, int posY, int height, int width, string path, Graphics &graphics);
	~Spider();

	void AI(vector<HitBox> mapTiles);
	void updateOffset(float mX, float mY);

	bool updateHealth(signed int amntToUpdate);

	void draw(Graphics &graphics);
	void update(Uint32 elapsedTime, vector<HitBox>);

	HitBox getHitBox();
private:
	Direction _direction1;
	Direction _direction2;

	bool checkCollision(vector<HitBox> mapTiles);

	Sprite _sprite;
	HitBox _hitBox;

	float _x, _y;
	float _mX, _mY; //offset

	int _health;
};

#endif