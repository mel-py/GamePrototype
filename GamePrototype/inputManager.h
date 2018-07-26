#ifndef  INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL.h>
#include <map>

using namespace std;

class InputManager {
public:
	void update();

	void KeyUpEvent(SDL_Event& e);
	void KeyDownEvent(SDL_Event& e);

	bool isKeyDown(int key);
	bool isKeyUp(int key);
	bool isKeyHeld(int key);
private:
	bool _keyDown[323];
	bool _keyUp[323];
	bool _keyPressed[323];
};

#endif
