#ifndef ENEMY_H
#define ENEMY_H

#include "graphics.h"
#include "sprite.h"
#include "globals.h"

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

	Direction _direction;
	float _x, _y;
};

#endif