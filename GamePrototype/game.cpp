#include "game.h"
#include <stdio.h>
#include <SDL.h>

using namespace std;

Game::Game() {
	Graphics graphics;
	this->testSprite = Sprite(400, 400, "Sprites/link.png", graphics);
	game_loop(graphics);
}

Game::~Game() {}

void Game::game_loop(Graphics &graphics) {
	while (true) {
		draw(graphics);
	}
}

void Game::draw(Graphics &graphics) {
	graphics.clear();

	testSprite.draw(graphics);

	graphics.flip();
}