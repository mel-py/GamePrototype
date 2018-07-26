#include "game.h"
#include <stdio.h>
#include <SDL.h>

using namespace std;

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	this->_posx = 100;
	this->_posy = 100;
	game_loop();
}

Game::~Game() {}

void Game::game_loop() {
	Graphics graphics;
	this->_player = Player(this->_posx, this->_posy, "Sprites/link.png", graphics);
	this->_player.stopMoving();
	SDL_Event e;

	while (true) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				return;
			} else if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_w:
					this->_player.movePlayer("backwards");
					break;
				case SDLK_s:
					this->_player.movePlayer("forwards");
					break;
				case SDLK_a:
					this->_player.movePlayer("left");
					break;
				case SDLK_d:
					this->_player.movePlayer("right");
					break;
				}
			} else if (e.type == SDL_KEYUP) {
				this->_player.stopMoving();
			}
		}

		Uint32 elapsedTime = SDL_GetTicks();
		update(elapsedTime);
		draw(graphics);
	}
}

void Game::draw(Graphics &graphics) {
	graphics.clear();
	this->_player.draw(graphics);
	graphics.flip();
}

void Game::update(Uint32 elapsedTime) {
	this->_player.update(elapsedTime);
}