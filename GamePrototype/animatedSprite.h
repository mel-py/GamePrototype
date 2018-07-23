#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPIRTE_H

#include "sprite.h"
#include "graphics.h"
#include <string>
#include <SDL.h>
#include <vector>

using namespace std;

class AnimatedSprite : public Sprite {
public:
	AnimatedSprite();
	//frames stores the number of frames in the animation
	AnimatedSprite(int x, int y, int width, int height, int sourceX, int sourceY, const string path, Graphics &graphics, int frames);

	void draw(int x, int y, Graphics &graphics);
	void update(Uint32 elapsedTime);
private:
	vector<SDL_Rect> _sourceRects;

	Uint32 _lastUpdatedTime;
	Uint32 _timeToUpdate;
	int _numFrames;
	int _frame;
};

#endif