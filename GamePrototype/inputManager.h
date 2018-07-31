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

	bool isKeyDown(SDL_Scancode key);
	bool isKeyUp(SDL_Scancode key);
	bool isKeyHeld(SDL_Scancode key);
private:
	bool _keyDown[323];
	bool _keyUp[323];
	bool _keyPressed[323];
};

#endif
