#ifndef GAME_H
#define GAME_H

#include "graphics.h"
#include "sprite.h"

class Game {
public:
	Game();
	~Game();

	void game_loop();
	void draw(Graphics &graphics);
private:
	Sprite _testSprite;

	int _posx, _posy;
};

#endif