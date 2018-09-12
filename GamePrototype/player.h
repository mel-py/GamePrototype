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

	HitBox getHitBox();
	Direction* getDirection();

	void beginNewFrame();

	void update(Uint32 elapsedTime);
	void draw(Graphics &graphics);
private:
	map<Direction, AnimatedSprite> _sprites;
	float _x, _y;
	HitBox _hitBox;

	Direction _directions[2]; //since the player can move in two directions at once store it as a 2d array
	/*
	Since the player can move in two directions at once (i.e. forward and left) we need to know if the first or second direction
	in the array has been updated last (i.e. forward was already stored in the array so store left in the second array element)
	*/
	int _directionIndex;
};

#endif
