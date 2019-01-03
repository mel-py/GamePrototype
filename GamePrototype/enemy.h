#ifndef ENEMY_H
#define ENEMY_H

#include "graphics.h"
#include "sprite.h"
#include "globals.h"
#include <vector>
#include "hitBox.h"

using namespace std;

class Enemy {
public:
	Enemy();
	Enemy(int x, int y, int posX, int posY, int height, int width, string path, Graphics &graphics);
	~Enemy();

	//AI that decides the enemy's movement
	void AI();

	void updateOffset(float mX, float mY);

	void draw(Graphics &graphics);
	void update(Uint32 elapsedTime);

	bool checkCollision(vector<HitBox> mapTiles);
private:
	Sprite _sprite;
	HitBox _hitBox;

	Direction _direction;
	float _x, _y;
};

#endif