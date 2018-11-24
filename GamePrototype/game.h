#ifndef GAME_H
#define GAME_H

#include "graphics.h"
#include "Player.h"
#include "Map.h"
#include <vector>
#include "slime.h"

class Game {
public:
	Game();
	~Game();

	void game_loop();
	void draw(Graphics &graphics);
	void update(Uint32 elapsedTime, Graphics &graphics);
private:
	Player _player;
	Direction _playerDirection;
	float _newPositionX, _newPositionY; //keep track of how far we are moving the player for collision detection
	vector<Slime> _enemies;
	Map _map;
	Tile _testTile;

	int _mapOffsetX, _mapOffsetY;
	Vector2 _mapSize;
};

#endif