#include "Explosion.h"
#include "SDL_gfx/SDL2_gfxPrimitives.h"
#include <iostream>

SDL_Surface* Explosion::mSurface = nullptr;
float Explosion::mMaxRadius = 40;


Explosion::Explosion(SDL_Point point):
	mCenter(point),
	mTempRadius(0),
	mUpdateRate(35)
{
}

Uint32 Color() {
	int temp = rand() % 101;
	if (temp <= 40)
		return 0xff00ffff;
	return 0xff0000ff;
}

void Explosion::Draw(SDL_Renderer *mRenderer)
{
	filledCircleColor(mRenderer, mCenter.x, mCenter.y, mTempRadius,Color());
}

void Explosion::Update(float delta)
{
	mTempRadius += mUpdateRate*delta;

	if (mTempRadius <= 0) {
		mTempRadius = 0;
		return;
	}

	if (mTempRadius >= mMaxRadius)
		mUpdateRate = -mUpdateRate;
}


