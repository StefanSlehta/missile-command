#include "Turret.h"
#include "SDL_gfx/SDL2_gfxPrimitives.h"
#include <iostream>

Turret::Turret()
{

}

Turret::Turret(SDL_Point start, SDL_Point end) :
	mStartPosition(start),
	mEndPosition(end),
	mActive(true)
{

}

void Turret::Face(double slope) {
	mEndPosition.x = mStartPosition.x + SDL_cos(slope) * len;
	mEndPosition.y = mStartPosition.y - SDL_sin(slope) * len;
}

bool Turret::IsActive()
{
	return mActive;
}

SDL_Point Turret::FirePostion()
{
	return SDL_Point();
}

void Turret::Draw(SDL_Renderer * renderer) const
{
	thickLineColor(renderer, mStartPosition.x, mStartPosition.y, mEndPosition.x, mEndPosition.y, 10, 0xffffffff);
}