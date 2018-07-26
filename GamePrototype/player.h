#ifndef PLAYER_H
#define PLAYER_H

#include "animatedSprite.h"
#include "graphics.h"
#include <map>
#include <string>

using namespace std;

enum Direction { LEFT, RIGHT, BACKWARD, FORWARD };

class Player {
public:
	Player();
	Player(int x, int y, string path, Graphics &graphics);
	~Player();

	void movePlayer(string direction);
	void stopMoving();

	void update(Uint32 elapsedTime);
	void draw(Graphics &graphics);
private:
	map<Direction, AnimatedSprite> _sprites;
	float _x, _y;
	float _speed; //current speed of the character

	Direction _direction; //current direction the player is facing
};

#endif
