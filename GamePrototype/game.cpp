#include "game.h"
#include "inputManager.h"
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
	InputManager input;

	while (true) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				return;
			} else if (e.type == SDL_KEYDOWN) {
				input.KeyDownEvent(e);
			} else if (e.type == SDL_KEYUP) {
				input.KeyUpEvent(e);
			}
		}
		if (input.isKeyDown(SDL_SCANCODE_ESCAPE) == true) {
			return;
		} else {
			if (input.isKeyDown(SDL_SCANCODE_W) == true) {
				this->_player.movePlayer("backwards");
			} 
			if (input.isKeyDown(SDL_SCANCODE_S) == true) {
				this->_player.movePlayer("forwards");
			} 
			if (input.isKeyDown(SDL_SCANCODE_A) == true) {
				this->_player.movePlayer("left");
			} 
			if (input.isKeyDown(SDL_SCANCODE_D) == true) {
				this->_player.movePlayer("right");
			}	
			if (input.isKeyHeld(SDL_SCANCODE_W) == false && input.isKeyHeld(SDL_SCANCODE_S) == false
				&& input.isKeyHeld(SDL_SCANCODE_A) == false && input.isKeyHeld(SDL_SCANCODE_D) == false) {
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