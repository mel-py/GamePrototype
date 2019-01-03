#include "game.h"
#include "inputManager.h"
#include <stdio.h>
#include <SDL.h>
#include "map.h"
#include "Vector2.h"
#include <iostream>
#include "globals.h"
#include <time.h>

using namespace std;

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);

	game_loop();
}

Game::~Game() {}

void Game::game_loop() {
	Graphics graphics;
	Vector2 resolution = graphics.getResolution();
	this->_map = Map("Maps/map0.tmx", "Sprites/map1.png", 8, 13, graphics);
	this->_player = Player(resolution.x / 2, resolution.y / 2, "Sprites/notlink.png", graphics);
	this->_player.stopMoving();
	this->_playerDirection = NONE;
	vector<Vector2> enemySpawns = this->_map.getEnemySpawns();
	this->_spiders.push_back(Spider(65, 100, 0, 0, 16, 32, "Sprites/spider.png", graphics));
	for (int i = 0; i < enemySpawns.size(); i++) {
		Vector2 current = enemySpawns.at(i);
		this->_enemies .push_back(Slime(current.x, current.y, 0, 0, 16, 16, "Sprites/smushroom.png", graphics));
	}
	SDL_Event e;
	InputManager input;
	bool offset; //false if the map offset is not able to move but a button is pressed

	while (true) {
		//input.beginNewFrame();
		this->_newPositionX = 0;
		this->_newPositionY = 0;

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
			if (input.isKeyDown(SDL_SCANCODE_SPACE) == true) {
				this->_player.attack();
			} else {
				if (input.isKeyDown(SDL_SCANCODE_W) == true) {
					this->_newPositionY = 0.1;
					this->_playerDirection = BACKWARD;
					this->_player.movePlayer(BACKWARD);
				} 
				if (input.isKeyDown(SDL_SCANCODE_S) == true) {
					this->_newPositionY = -0.1;
					this->_playerDirection = FORWARD;
					this->_player.movePlayer(FORWARD);
				} 
				if (input.isKeyDown(SDL_SCANCODE_A) == true) {
					this->_newPositionX = 0.1;
					this->_playerDirection = LEFT;
					this->_player.movePlayer(LEFT);
				}
				if (input.isKeyDown(SDL_SCANCODE_D) == true) {
					this->_newPositionX = -0.1;
					this->_playerDirection = RIGHT;
					this->_player.movePlayer(RIGHT);
				}
				if (input.isKeyDown(SDL_SCANCODE_W) == false && input.isKeyDown(SDL_SCANCODE_S) == false
					&& input.isKeyDown(SDL_SCANCODE_A) == false && input.isKeyDown(SDL_SCANCODE_D) == false) {
					this->_player.stopMoving();
					this->_playerDirection = NONE;
				}
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
	this->_spiders.at(0).draw(graphics);
	for (int i = 0; i < this->_enemies.size(); i++) {
		this->_enemies.at(i).draw(graphics);
	}
	graphics.flip();
}

void Game::update(Uint32 elapsedTime, Graphics &graphics) {
	this->_player.update(elapsedTime);
	for (int i = 0; i < this->_enemies.size(); i++) {
		this->_enemies.at(i).update(elapsedTime);
	}
	this->_spiders.at(0).update(elapsedTime, this->_map.getHitBoxes());
	
	if (this->_playerDirection != NONE) {
		Vector2 resolution = graphics.getResolution();

		//check the x direction
		if (this->_newPositionX != 0) {
			bool offset = this->_map.updateOffset(this->_newPositionX, 0.0, resolution, this->_player.getPlayerOffset());
			if (offset == false) {
				this->_player.updatePlayerOffset(this->_newPositionX * -1, 0.0);
			}
			bool collision = this->_map.checkCollisions(this->_player.getHitBox());
			if (collision) {
				if (offset) {
					this->_map.updateOffset(this->_newPositionX * -1, 0.0, resolution, this->_player.getPlayerOffset());
				} else {
					this->_player.updatePlayerOffset(this->_newPositionX, 0);
				}
			} else if (offset) {
				for (int i = 0; i < this->_enemies.size(); i++) {
					this->_enemies.at(i).updateOffset(this->_newPositionX, 0.0);
				}
			}
		}

		//check the y direction
		if (this->_newPositionY != 0) {
			bool offset = this->_map.updateOffset(0.0, this->_newPositionY, resolution, this->_player.getPlayerOffset());
			if (offset == false) {
				this->_player.updatePlayerOffset(0.0, this->_newPositionY * -1);
			}
			bool collision = this->_map.checkCollisions(this->_player.getHitBox());
			if (collision) {
				if (offset) {
					this->_map.updateOffset(0.0, this->_newPositionY * -1, resolution, this->_player.getPlayerOffset());
				} else {
					this->_player.updatePlayerOffset(0, this->_newPositionY);
				}
			} else if (offset) {
				for (int i = 0; i < this->_enemies.size(); i++) {
					this->_enemies.at(i).updateOffset(0.0, this->_newPositionY);
				}
			}
		}
	}

	for (int i = 0; i < this->_enemies.size(); i++) {
		bool collision = this->_map.checkCollisions(this->_enemies.at(i).getHitBox());
		if (collision) {
			this->_enemies.at(i).handleCollision();
		}
		if (this->_player.getHitBox().checkCollision(this->_enemies.at(i).getHitBox())) {
			if (this->_player.isAttacking()) {
				bool dead = this->_enemies.at(i).updateHealth(-10);
				if (dead) {
					this->_enemies.erase(this->_enemies.begin() + i);
					this->_player.addExp(40);
				}
			} else if (elapsedTime % 500 == 0) {
				this->_player.updateHealth(-1);
			}
		}
	}
}