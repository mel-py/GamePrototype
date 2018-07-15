#ifndef GAME_H
#define GAME_H

#include "graphics.h"
#include "sprite.h"

class Game {
public:
	Game();
	~Game();
	void game_loop(Graphics &graphics);
private:
	void draw(Graphics &graphics);

	Sprite testSprite;
};

#endif