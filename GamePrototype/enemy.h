#ifndef ENEMY_H
#define ENEMY_H

#include "graphics.h"
#include "hitBox.h"
#include "sprite.h"

using namespace std;

class Enemy {
public:
	Enemy();
	Enemy(int x, int y, int posX, int posY, int height, int width, string path, Graphics &graphics);
	~Enemy();

	//AI that decides the enemy's movement
	void AI();

	void draw(Graphics &graphics);
	void update(Uint32 elapsedTime);

private:
	Sprite _sprite;

	float _x, _y;
	HitBox _hitbox;
};

#endif