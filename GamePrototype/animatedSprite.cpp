#include "animatedSprite.h"

AnimatedSprite::AnimatedSprite() {};

AnimatedSprite::AnimatedSprite(int x, int y, int width, int height, int sourceX, int sourceY, const string path, Graphics &graphics, int frames, float updateTime) :
	Sprite(x, y, width, height, sourceX, sourceY, path, graphics) {
	this->_numFrames = frames;
	for (int i = 0; i < frames; i++) {
		SDL_Rect newSprite = {sourceX + (i*width), sourceY, width, height};
		this->_sourceRects.push_back(newSprite);
	}

	this->_timeToUpdate = updateTime;
	this->_lastUpdatedTime = 0;
	this->_frame = 0;
};

void AnimatedSprite::stopAnimation() {
	this->_playAnimation = false;
	this->_frame = 0;
}

void AnimatedSprite::playAnimation() {
	this->_playAnimation = true;
}

void AnimatedSprite::update(Uint32 elapsedTime) {
	if (this->_playAnimation) {
		if (elapsedTime - this->_lastUpdatedTime > this->_timeToUpdate) {
			this->_frame++;
			if (this->_frame >= this->_numFrames) {
				this->_frame = 0;
			}
			this->_lastUpdatedTime = elapsedTime;
		}
	}
}

void AnimatedSprite::draw(int x, int y, Graphics &graphics) {
	SDL_Rect destRect = { x, y, this->_sourceRect.w * 2, this->_sourceRect.h * 2 };
	graphics.blitSurface(this->_sprite, &this->_sourceRects.at(this->_frame), &destRect);
}