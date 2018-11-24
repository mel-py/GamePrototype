#include "inputManager.h"

void InputManager::update() {

}

void InputManager::beginNewFrame() {
	this->_keyDown.clear();
	this->_keyUp.clear();
}

void InputManager::KeyUpEvent(SDL_Event& e) {
	this->_keyUp[e.key.keysym.scancode] = true;
	this->_keyDown[e.key.keysym.scancode] = false;
	this->_keyPressed[e.key.keysym.scancode] = false;
}

void InputManager::KeyDownEvent(SDL_Event& e) {
	this->_keyDown[e.key.keysym.scancode] = true;
	this->_keyPressed[e.key.keysym.scancode] = true;
}

bool InputManager::isKeyDown(SDL_Scancode key) {
	return this->_keyDown[key];
}

bool InputManager::isKeyHeld(SDL_Scancode key) {
	return this->_keyPressed[key];
}

bool InputManager::isKeyUp(SDL_Scancode key) {
	return this->_keyUp[key];
}