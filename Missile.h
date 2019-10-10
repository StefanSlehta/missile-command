#pragma once
#include<SDL.h>

class Missile {
private:
	float mPosX;
	float mPosY;
	
	bool mHostile;
	bool mValid;

	float mVelX;
	float mVelY;

	int mTargetIndex;
	bool mTargetCity;

	SDL_Color mTrajectoryColor;
	SDL_Point mOriginalPosition;

	SDL_Point mTargetPosition;

public:
	Missile(SDL_Point Position, bool Hostile, int Level,SDL_Point TargetPosition, int Index, bool City);

	float getPositionX() { return mPosX; }
	void setPositionX(float pos) { mPosX = pos; }

	float getPositionY() { return mPosY; }
	void setPositionY(float pos) { mPosY; }

	bool TargetCity() { return mTargetCity; }
	int TargetIndex() { return mTargetIndex; }

	SDL_Point GetPosition() { return{ int(mPosX),int(mPosY) }; }

	bool isHostile() { return mHostile; }
	void Draw(SDL_Renderer*);
	void Update(float delta);

	bool Hit();
	bool Valid() const{ return mValid; }

	void Invalidate() { mValid = false; }
};