#pragma once
#include<SDL.h>

class Explosion {
private:
	SDL_Point mCenter;
	static float mMaxRadius;
	float mUpdateRate;
	float mTempRadius;

public:
	static SDL_Surface* mSurface;
	Explosion(SDL_Point);
	
	bool Collides(SDL_Point* point) { return mTempRadius >= sqrt(pow(mCenter.x - point->x, 2) + pow(mCenter.y - point->y,2)); }

	void Draw(SDL_Renderer*);
	void Update(float delta);
	bool Valid()const { return mTempRadius > 0; }
};