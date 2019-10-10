#include "Ship.h"

SDL_Texture* Ship::mShip = nullptr;
SDL_Rect Ship::mShipRect = { 0,0,0,0 };

Ship::Ship() :
	mPosX(0),
	mPosY(rand() % 100 + 100),
	mVel(rand() % 100 + 50)
{
	mShipRect.y = mPosY;
}

bool Ship::Shoot() {
	return rand() % 101 > 80;
}

void Ship::LoadShip(SDL_Renderer* renderer) {
	if (mShip == nullptr) {
		SDL_Surface * surf = SDL_LoadBMP("Ship.bmp");
		SDL_SetColorKey(surf, SDL_TRUE, 0xffff00ff);
		mShip = SDL_CreateTextureFromSurface(renderer, surf);
		SDL_FreeSurface(surf);
	}
	SDL_QueryTexture(mShip, nullptr, nullptr, &mShipRect.w, &mShipRect.h);
}

void Ship::Draw(SDL_Renderer* renderer) {
	mShipRect.x = int(mPosX);
	SDL_RenderCopyEx(renderer, mShip, nullptr, &mShipRect, 0, nullptr, SDL_FLIP_HORIZONTAL);
}

void Ship::Update(float delta)
{
	mPosX += mVel*delta;
}

