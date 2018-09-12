#include "game.h"
#include "inputManager.h"
#include <stdio.h>
#include <SDL.h>
#include "map.h"
#include "Vector2.h"
#include <iostream>
#include "globals.h"

using namespace std;

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	game_loop();
}

Game::~Game() {}

void Game::game_loop() {
	Graphics graphics;
	Vector2 resolution = graphics.getResolution();
	this->_player = Player(resolution.x / 2, resolution.y / 2, "Sprites/notlink.png", graphics);
	this->_player.stopMoving();
	this->_enemies.push_back(Enemy(0, 0, 16, 16, 0, 0, "Sprites/smushroom.png", graphics));
	SDL_Event e;
	InputManager input;
	this->_map = Map("Maps/map0.tmx", "Sprites/map1.png", 8, 13, graphics);
	bool offset; //false if the map offset is not able to move but a button is pressed

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
			this->_player.beginNewFrame();
			if (input.isKeyDown(SDL_SCANCODE_W) == true) {
				this->_player.movePlayer(BACKWARD);
				offset = this->_map.updateOffset(0.0, 0.1, resolution, this->_player.getPlayerOffset());
				if (offset == false) {
					this->_player.updatePlayerOffset(0.0, -0.1);
				}
			} 
			if (input.isKeyDown(SDL_SCANCODE_S) == true) {
				this->_player.movePlayer(FORWARD);
				offset = this->_map.updateOffset(0.0, -0.1, resolution, this->_player.getPlayerOffset());
				if (offset == false) {
					this->_player.updatePlayerOffset(0.0, 0.1);
				}
			} 
			if (input.isKeyDown(SDL_SCANCODE_A) == true) {
				this->_player.movePlayer(LEFT);
				offset = this->_map.updateOffset(0.1, 0.0, resolution, this->_player.getPlayerOffset());
				if (offset == false) {
					this->_player.updatePlayerOffset(-0.1, 0.0);
				}
			} 
			if (input.isKeyDown(SDL_SCANCODE_D) == true) {
				this->_player.movePlayer(RIGHT);
				offset = this->_map.updateOffset(-0.1, 0.0, resolution, this->_player.getPlayerOffset());
				if (offset == false) {
					this->_player.updatePlayerOffset(0.1, 0.0);
				}
			} 
			if (input.isKeyHeld(SDL_SCANCODE_W) == false && input.isKeyHeld(SDL_SCANCODE_S) == false
				&& input.isKeyHeld(SDL_SCANCODE_A) == false && input.isKeyHeld(SDL_SCANCODE_D) == false) {
				this->_player.stopMoving();
			}
		}

		Uint32 elapsedTime = SDL_GetTicks();
		update(elapsedTime, graphics);
		draw(graphics);
	}
}

void Game::draw(Graphics &graphics) {
	graphics.clear();
	this->_map.draw(graphics);
	this->_player.draw(graphics);
	for (int i = 0; i < this->_enemies.size(); i++) {
		this->_enemies.at(i).draw(graphics);
	}
	graphics.flip();
}

void Game::update(Uint32 elapsedTime, Graphics &graphics) {
	this->_player.update(elapsedTime);

	bool collision = this->_map.checkCollisions(this->_player.getHitBox());
	if (collision) {
		Direction *direcs = this->_player.getDirection();
		for (int i = 0; i < 2; i++) {
			switch (direcs[i]) {
			case (BACKWARD):
				if (!this->_map.updateOffset(0.0, -0.1, graphics.getResolution(), this->_player.getPlayerOffset())) {
					this->_player.updatePlayerOffset(0.0, 0.1);
				}
				break;
			case (FORWARD):
				if (!this->_map.updateOffset(0.0, 0.1, graphics.getResolution(), this->_player.getPlayerOffset())) {
					this->_player.updatePlayerOffset(0.0, -0.1);
				}
				break;
			case (LEFT):
				if (!this->_map.updateOffset(-0.1, 0.0, graphics.getResolution(), this->_player.getPlayerOffset())) {
					this->_player.updatePlayerOffset(0.1, 0.0);
				}
				break;
			case (RIGHT):
				if (!this->_map.updateOffset(0.1, 0.0, graphics.getResolution(), this->_player.getPlayerOffset())) {
					this->_player.updatePlayerOffset(-0.1, 0.0);
				}
				break;
			case (NONE):
				break;
			}
		}
	}
}