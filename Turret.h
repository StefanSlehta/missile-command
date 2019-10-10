#pragma once
#include <SDL.h>

class Turret{
private:
	bool mActive;
	SDL_Point mStartPosition;
	SDL_Point mEndPosition;
	int mMissileCount;
	int len = 30;

public:
	Turret();
	Turret(SDL_Point start,SDL_Point end);

	bool		IsActive();
	SDL_Point	GetStartPostition() const{ return mStartPosition; }
	SDL_Point	GetEndPostition()const { return mEndPosition; }
	SDL_Point	FirePostion();

	bool		CanFire() { return mActive && mMissileCount > 0; }
	void		Fire() { mMissileCount--; }
	void		Invalidate() { mActive = false; }
	void		Activate() { mActive = true; }
	void		SetMissileCount(int Level, int Spawning,int TurretsLeft) { mMissileCount = (Spawning / TurretsLeft + 5 - (Level >= 5 ? 4 : Level)); }
	int			GetMissileCount()const {	return mMissileCount;}
	void Face(double slope);
	void Draw(SDL_Renderer *renderer) const;
};