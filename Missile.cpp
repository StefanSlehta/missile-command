#include "Missile.h"
#include <iostream>

Missile::Missile(SDL_Point Position, bool Hostile, int Level,SDL_Point TargetPosition,int Index,bool City) :
	mPosX(Position.x),
	mPosY(Position.y),
	mHostile(Hostile),
	mOriginalPosition(Position),
	mTargetPosition(TargetPosition),
	mValid(true),
	mTargetCity(City),
	mTargetIndex(Index)
{
	mVelX = Hostile ? (50 * pow(1.25, Level) > 150 ? 150 : 20 * pow(1.2, Level)) : 350;
	mVelY = Hostile ? (50 * pow(1.25, Level) > 150 ? 150 : 20 * pow(1.2, Level)) : 350;
	double ang = atan2(TargetPosition.y - Position.y, TargetPosition.x - Position.x);
	mVelX *= cos(ang);
	mVelY *= sin(ang);
	if (Hostile)
		mTrajectoryColor = { 255,0,255,255 };
	else mTrajectoryColor = { 0,255,0,255 };
}

void Missile::Draw(SDL_Renderer* mRenderer) {
	SDL_SetRenderDrawColor(mRenderer, mTrajectoryColor.r, mTrajectoryColor.g, mTrajectoryColor.b, 255);
	SDL_RenderDrawLine(mRenderer, mOriginalPosition.x, mOriginalPosition.y, int(mPosX), int(mPosY));
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	SDL_RenderDrawPoint(mRenderer, int(mPosX), int(mPosY));
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
}

void Missile::Update(float delta) {
	mPosX += mVelX * delta;
	mPosY += mVelY * delta;
}

bool Missile::Hit() {
	if (mHostile)
		mValid = !(mPosY >= mTargetPosition.y);
	else mValid = !(mPosY <= mTargetPosition.y);
	return !mValid;
}
