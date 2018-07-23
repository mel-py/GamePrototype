#ifndef GAME_H
#define GAME_H

#include "graphics.h"
#include "animatedSprite.h"

class Game {
public:
	Game();
	~Game();

	void game_loop();
	void draw(Graphics &graphics);
	void update(Uint32 elapsedTime);
private:
	AnimatedSprite _testSprite;

	int _posx, _posy;
};

#endif