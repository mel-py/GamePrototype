#ifndef GAME_H
#define GAME_H

#include "graphics.h"
#include "Player.h"
#include "Map.h"

class Game {
public:
	Game();
	~Game();

	void game_loop();
	void draw(Graphics &graphics);
	void update(Uint32 elapsedTime);
private:
	Player _player;
	Map _map;
	Tile _testTile;

	int _posx, _posy;
};

#endif