#pragma once
#ifndef GAME_H_
#define GAME_H_

#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <list>
#include <string>
#include "Missile.h"
#include "Turret.h"
#include "City.h"
#include "Explosion.h"
#include "Ship.h"

class Game{
	int					mScreenWidth;
	int					mScreenHeight;
	Uint32				mLast;
	int					mWaitTime;
	SDL_Point			mMousePosition;
	SDL_Window*			mWindow;
	const Uint8*		mKeys;
	SDL_Renderer*		mRenderer;
	SDL_Texture*		mGround;
	Ship*				mShip;
	int					mScore;
	SDL_Texture*		mAshes;
	SDL_Rect			mGroundRect;
	SDL_Rect			mAshesRect;

	bool				mShouldQuit;
	int					mTurretState;
	int					mLevel;
	int					mMissilesLeft;
	bool				mNextLevelWait;

	std::vector<Missile> mMissiles;
	std::vector<Turret> mTurrets;
	std::vector<City> mCities;
	std::vector<Explosion> mExplosions;

	Turret*				mSelectedTurret;
private:
	bool				Initialize();
	void				Load();
	void				Shutdown();
	bool				LevelCleared();
	bool				GameOver();

	void				NextLevel();
	int					CalculateMissiles();
	Uint32				WaitTime();

	Uint32				DeltaTime();
	void				ProcessEvents();

	void				OnQuit();
	void				OnWindowResized(int w, int h);
	void				OnKeyDown(const SDL_KeyboardEvent* kbe);
	void				OnKeyUp(const SDL_KeyboardEvent* kbe);
	void				OnMouseDown(const SDL_MouseButtonEvent* mbe);
	void				OnMouseUp(const SDL_MouseButtonEvent* mbe);
	void				OnMouseMotion(const SDL_MouseMotionEvent* mme);
	void				DrawMarker();
	void				Update(float delta);
	void				Draw();

	void				SpawnMissile(bool hostile,SDL_Point* click,bool fromShip);

public: 
	Game();
	bool				Run();
};
#endif