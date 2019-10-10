#include "Game.h"
#include "Explosion.h"
#include "TextManager.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

Game::Game()
	:mScreenHeight(700)
	, mScreenWidth(768)
	, mWindow(nullptr)
	, mKeys(nullptr)
	, mRenderer(nullptr)
	, mShouldQuit(false)
	, mTurretState()
	, mGround(nullptr)
	, mLevel(1)
	, mAshes(nullptr)
	, mShip(nullptr)
	, mScore(0)
	, mNextLevelWait(false)

{
}

bool Game::Run()
{
	// setup
	if (!Initialize()) {
		std::cerr << "*** Game initialization failed" << std::endl;
		return false;
	}
	float const FPS = 30.0f;
	float const DELTA_F = 1.0f / FPS;
	unsigned int const DELTA_MS = (int)(DELTA_F * 1000.0f);
	unsigned int currentTime = SDL_GetTicks();
	unsigned int gameTime = currentTime;
	int const FRAME_SKIP = 6;

	mLast = SDL_GetTicks();
	mWaitTime = WaitTime();
	// game loop
	while (!mShouldQuit) {
		ProcessEvents();
		int updates = 0;
		if (GameOver()) 
			continue;
		if ((mWaitTime -= DeltaTime()) <= 0 && mMissilesLeft > 0) {
			SpawnMissile(true,nullptr,false);
			if (mShip == nullptr && rand() % 101 > 85 - mLevel)
				mShip = new Ship();
			mWaitTime = WaitTime();
		}
		while ((currentTime = SDL_GetTicks()) > gameTime && ++updates < FRAME_SKIP) {
			gameTime += DELTA_MS;
			if (LevelCleared() && !GameOver()) {// start next level
				NextLevel();
			}
			Update(DELTA_F);
		}
		//Render
		Draw();
	}

	// cleanup
	Shutdown();

	return true;
}

bool Game::Initialize()
{
	std::cout << "Initializing game" << std::endl;

	// initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "*** Failed to initialize SDL: " << SDL_GetError() << std::endl;
		return false;
	}

	// create a window
	mWindow = SDL_CreateWindow("Missile Command",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		mScreenWidth, mScreenHeight,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (!mWindow) {
		std::cerr << "*** Failed to create window: " << SDL_GetError() << std::endl;
		return false;
	}

	// get a pointer to keyboard state managed by SDL
	mKeys = SDL_GetKeyboardState(NULL);

	// create a renderer that takes care of drawing stuff to the window
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer) {
		std::cerr << "*** Failed to create renderer: " << SDL_GetError() << std::endl;
		return false;
	}

	if (!TextManager::Load())
		return false;

	Load();

	mSelectedTurret = &mTurrets[1];

	return true;
}

void Game::Load()
{
	mScore = 0;
	mLevel = 1;

	mMissilesLeft = CalculateMissiles();
	// Load and set ground
	if (mGround == nullptr) {
		SDL_Surface * surf = SDL_LoadBMP("Ground.bmp");
		SDL_SetColorKey(surf, SDL_TRUE, 0xffff00ff);
		mGround = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf);
	}
	if (mAshes == nullptr) {
		SDL_Surface * surf = SDL_LoadBMP("Ashes.bmp");
		SDL_SetColorKey(surf, SDL_TRUE, 0xffff00ff);
		mAshes = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf);
	}
	Ship::LoadShip(mRenderer);

	SDL_QueryTexture(mGround, nullptr, nullptr, &mGroundRect.w, &mGroundRect.h);
	SDL_QueryTexture(mAshes, nullptr, nullptr, &mAshesRect.w, &mAshesRect.h);

	mGroundRect.x = 0;
	mGroundRect.y = mScreenHeight - mGroundRect.h;

	mMissiles = std::vector<Missile>();
	mTurrets = std::vector<Turret>();
	mCities = std::vector<City>();
	mExplosions = std::vector<Explosion>();

	// Initialize Turrets
	SDL_Point turretStart = { 30,630 };
	SDL_Point turrentEnd = { turretStart.x,turretStart.y - 30 };
	int move = 355;
	for (int i = 0; i < 3; i++) {
		Turret temp = Turret(turretStart, turrentEnd);
		temp.SetMissileCount(mLevel,mMissilesLeft,3);
		mTurrets.push_back(temp);
		turretStart.x += move;
		turrentEnd.x = turretStart.x;
	}

	// Initialize Cities
	SDL_Point cityStart = {130, 630};
	move = 75;
	for (int i = 0; i < 6; i++) {
		if (i == 3)
			cityStart.x += 115;
		City temp = City(cityStart, 25, 35, true);
		mCities.push_back(temp);
		cityStart.x += move;
	}

}

void Game::Shutdown()
{
	std::cout << "Shutting down game" << std::endl;
	TTF_Quit();
	// this closes the window and shuts down SDL
	SDL_Quit();
}

bool Game::LevelCleared()
{
	return mMissilesLeft <= 0 && mMissiles.size() == 0;
}

bool Game::GameOver()
{
	return !mTurrets[0].IsActive() && 
		!mTurrets[1].IsActive() && 
		!mTurrets[2].IsActive() && 
		LevelCleared();
}

void Game::NextLevel()
{
	mLevel++;
	mMissilesLeft = CalculateMissiles();
	
	int temp = 0;
	for (int i = 0; i < mTurrets.size(); i++)
		if (mTurrets[i].IsActive())
			temp++; 

	for (int i = 0; i < mTurrets.size(); i++) {
		if (mTurrets[i].IsActive()) {
			mScore += 5 * mLevel;
			mTurrets[i].SetMissileCount(mLevel, mMissilesLeft,temp);
		}
	}

	for (int i = 0; i < mCities.size(); i++) {
		if (mCities[i].IsActive())
			mScore += 100 * mLevel;
	}

	delete mShip;
	mShip = nullptr;

	mMissiles.clear();
	mExplosions.clear();
	mWaitTime = 5000; // 4sec wait time between levels;
	
}

int Game::CalculateMissiles()
{
	return int(10 * pow(1.5, mLevel));
}

Uint32 Game::WaitTime()
{
	Uint32 temp = Uint32(2500 - 20 * pow(2, mLevel));
	return temp >= 1000 ? temp : 1000;
}

bool IsValidMissile(const Missile& m) { return !m.Valid(); }
bool IsValidExplosion(const Explosion& e) { return !e.Valid(); }

void Game::Update(float delta)
{
	for (int i = 0; i < mMissiles.size(); i++) {
		Missile& CurrentMissile = mMissiles[i];
		CurrentMissile.Update(delta);
		SDL_Point MissilePosition = CurrentMissile.GetPosition();
		if (CurrentMissile.Hit()) {
			mExplosions.push_back(Explosion(CurrentMissile.GetPosition()));

			if (CurrentMissile.isHostile()) {
				if (CurrentMissile.TargetCity()) 
					mCities[CurrentMissile.TargetIndex()].SetActive(false);
				else 
					mTurrets[CurrentMissile.TargetIndex()].Invalidate();
			}
		}

		// our missiles don't explode from explosions..
		if (!CurrentMissile.isHostile()) continue;
		for (int j = 0; j < mExplosions.size(); j++) {
			if (mExplosions[j].Collides(&MissilePosition)) {
				mExplosions.push_back(Explosion(MissilePosition));
				CurrentMissile.Invalidate();
				mScore += 25 * mLevel; //mLevel is multiplier
				break;
			}
		}
	}

	// clear invalid missiles
	// inefficient, but didn't think the design through, should've used a list
	mMissiles.erase(
		std::remove_if(mMissiles.begin(), mMissiles.end(), IsValidMissile),
		mMissiles.end());
	
	for (int j = 0; j < mExplosions.size(); j++) {
		if (mShip != nullptr) {
			if (mExplosions[j].Collides(&mShip->BottomLeft()) ||
				mExplosions[j].Collides(&mShip->TopLeft()) ||
				mExplosions[j].Collides(&mShip->BottomRight()) ||
				mExplosions[j].Collides(&mShip->TopRight())) {
				mExplosions.push_back(Explosion(mShip->TopLeft()));
				delete mShip;
				mShip = nullptr;
				mScore += 50 * mLevel; 
				break;
			}
		}
	}

	for (int i = 0; i < mExplosions.size(); i++) 
		mExplosions[i].Update(delta);

	mExplosions.erase(
		std::remove_if(mExplosions.begin(), mExplosions.end(), IsValidExplosion),
		mExplosions.end());

	if (mShip != nullptr) {
		mShip->Update(delta);

		// SHIP SHOOTING, A LITTLE BIT OF A MISUNDERSTANDING HERE
		for (int i = 0; i < mTurrets.size(); i++)
			if (mTurrets[i].IsActive() && abs(mShip->TopLeft().x - mTurrets[i].GetStartPostition().x)<=1)
				if (rand() % 101 > 60)
					SpawnMissile(true, &mTurrets[i].GetStartPostition(),true);
		for(int i=0;i<mCities.size();i++)
			if(mCities[i].IsActive() && abs(mShip->TopLeft().x - mCities[i].GetPosition().x)<=1)
				if (rand() % 101 > 60)
					SpawnMissile(true, &mCities[i].GetPosition(),true);
	}
}

void Game::Draw()
{
	// clear the screen
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255); //black background
	SDL_RenderClear(mRenderer);
	SDL_RenderCopyEx(mRenderer, mGround, nullptr, &mGroundRect, 0, nullptr, SDL_FLIP_NONE);

	for (int i = 0; i < mTurrets.size(); i++) {
		if(mTurrets[i].IsActive())
			mTurrets[i].Draw(mRenderer);
		else {
			mAshesRect.x = mTurrets[i].GetStartPostition().x - mAshesRect.w / 2;
			mAshesRect.y = mTurrets[i].GetStartPostition().y - mAshesRect.h / 2;
			SDL_RenderCopyEx(mRenderer, mAshes, nullptr, &mAshesRect, 0, nullptr, SDL_FLIP_NONE);
		}
	}

	for (int i = 0; i < mCities.size(); i++) {
		if(mCities[i].IsActive())
			mCities[i].Draw(mRenderer);
		else {
			mAshesRect.x = mCities[i].GetPosition().x - mCities[i].GetWidth()/2;
			mAshesRect.y = mCities[i].GetPosition().y + mCities[i].GetHeight()/2;
			SDL_RenderCopyEx(mRenderer, mAshes, nullptr, &mAshesRect, 0, nullptr, SDL_FLIP_NONE);
		}
	}

	DrawMarker(); //draw the mouse cursor

	for (int i = 0; i < mMissiles.size(); i++)
		mMissiles[i].Draw(mRenderer);

	for (int i = 0; i < mExplosions.size(); i++)
		mExplosions[i].Draw(mRenderer);

	if (mShip != nullptr)
		mShip->Draw(mRenderer);

	TextManager::DrawScore(mRenderer, mScore, mScreenWidth);
	for (int i = 0; i < mTurrets.size(); i++)
		if (mTurrets[i].IsActive())
			TextManager::DrawMissileCount(mRenderer, &mTurrets[i]);

	if (GameOver())
		TextManager::DrawGameOver(mRenderer, mScreenWidth, mScreenHeight);

	else if (mNextLevelWait)
		TextManager::DrawNextLevelScreen(mRenderer, mLevel, mScreenHeight, mScreenWidth);

	SDL_RenderPresent(mRenderer);
}

Uint32 Game::DeltaTime() {
	Uint32 temp = SDL_GetTicks() - mLast;
	mLast = SDL_GetTicks();
	return temp;
}

void Game::SpawnMissile(bool hostile, SDL_Point* click,bool fromShip) {
	if (hostile) {
		mMissilesLeft--;
		// choose city
		bool chosen = false;
		bool city = rand() % 101 > 50;
		if (city)
			while (!chosen) {
				for (int i = 0; i < mCities.size(); i++) {
					if (mCities[i].IsActive()) {
						if (rand() % 100 > 70) {
							chosen = true;
							if(!fromShip)
								mMissiles.push_back(Missile({ rand() % 768, 0 }, hostile, mLevel, mCities[i].GetPosition(),i,true));
							else mMissiles.push_back(Missile({ mShip->BottomLeft().x+5, mShip->BottomLeft().y }, hostile, mLevel, mCities[i].GetPosition(), i, true));
							break;
						}
					}
				}
			}
		else {
			int turret;
			while (!mTurrets[turret = rand() % 3].IsActive());
			mMissiles.push_back(Missile({ rand() % 768, 0 }, hostile, mLevel, mTurrets[turret].GetStartPostition(),turret,false));
		}
		return;
	}
	mMissiles.push_back(Missile(mSelectedTurret->GetEndPostition(), hostile, mLevel, *click,0,false));
}