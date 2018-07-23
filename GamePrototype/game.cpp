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
	this->_testSprite = AnimatedSprite(this->_posx, this->_posy, 24, 32, 0, 0, "Sprites/link.png", graphics, 12);
	SDL_Event e;

	while (true) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				return;
			} else if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_w:
					this->_posy -= 2;
					break;
				case SDLK_s:
					this->_posy += 2;
					break;
				case SDLK_a:
					this->_posx -= 2;
					break;
				case SDLK_d:
					this->_posx += 2;
					break;
				}
			}
		}

		Uint32 elapsedTime = SDL_GetTicks();
		update(elapsedTime);
		draw(graphics);
	}
}

void Game::draw(Graphics &graphics) {
	graphics.clear();
	this->_testSprite.draw(this->_posx, this->_posy, graphics);
	graphics.flip();
}

void Game::update(Uint32 elapsedTime) {
	this->_testSprite.update(elapsedTime);
}