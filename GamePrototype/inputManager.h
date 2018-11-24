#ifndef  INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL.h>
#include <map>

using namespace std;

class InputManager {
public:
	void update();

	void beginNewFrame();

	void KeyUpEvent(SDL_Event& e);
	void KeyDownEvent(SDL_Event& e);

	bool isKeyDown(SDL_Scancode key);
	bool isKeyUp(SDL_Scancode key);
	bool isKeyHeld(SDL_Scancode key);
private:
	map<SDL_Scancode, bool> _keyDown;
	map<SDL_Scancode, bool> _keyUp;
	map<SDL_Scancode, bool> _keyPressed;
};

#endif
