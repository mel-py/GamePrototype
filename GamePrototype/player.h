#ifndef PLAYER_H
#define PLAYER_H

#include "animatedSprite.h"
#include "graphics.h"
#include "Vector2.h"
#include <map>
#include <string>
#include "globals.h"
#include "hitBox.h"

using namespace std;

class Player {
public:
	Player();
	Player(int x, int y, string path, Graphics &graphics);
	~Player();

	void movePlayer(Direction direction);
	void stopMoving();

	void updatePlayerOffset(float mX, float mY);
	Vector2 getPlayerOffset();

	void update(Uint32 elapsedTime);
	void draw(Graphics &graphics);
private:
	map<Direction, AnimatedSprite> _sprites;
	float _x, _y;
	HitBox _hitBox;

	Direction _direction; //current direction the player is facing
};

#endif
