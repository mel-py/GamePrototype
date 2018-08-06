#include "game.h"
#include "inputManager.h"
#include <stdio.h>
#include <SDL.h>
#include "map.h"
#include "Vector2.h"
#include <iostream>
using namespace std;

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	game_loop();
}

Game::~Game() {}

void Game::game_loop() {
	Graphics graphics;
	this->_player = Player(240, 320, "Sprites/notlink.png", graphics);
	this->_player.stopMoving();
	SDL_Event e;
	InputManager input;
	this->_map = Map("Maps/map0.tmx", "Sprites/map1.png", 8, 13, graphics);

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
				this->_map.updateOffset(0, 1);
			} 
			if (input.isKeyDown(SDL_SCANCODE_S) == true) {
				this->_player.movePlayer("forwards");
				this->_map.updateOffset(0, -1);
			} 
			if (input.isKeyDown(SDL_SCANCODE_A) == true) {
				this->_player.movePlayer("left");
				this->_map.updateOffset(1, 0);
			} 
			if (input.isKeyDown(SDL_SCANCODE_D) == true) {
				this->_player.movePlayer("right");
				this->_map.updateOffset(-1, 0);
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
	this->_map.draw(graphics);
	this->_player.draw(graphics);
	graphics.flip();
}

void Game::update(Uint32 elapsedTime) {
	this->_player.update(elapsedTime);
}