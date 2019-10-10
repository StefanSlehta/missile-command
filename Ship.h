#pragma once
#include <SDL.h>
#include <iostream>

class Ship{
private:
	static SDL_Texture* mShip;
	static SDL_Rect mShipRect;
	float mPosX;
	float mPosY;

	float mVel;
public:
	Ship();
	bool Shoot();

	static void LoadShip(SDL_Renderer* renderer);

	static SDL_Point TopLeft() { return{ mShipRect.x,mShipRect.y }; }
	static SDL_Point TopRight() { return{ mShipRect.x + mShipRect.w,mShipRect.y }; }
	static SDL_Point BottomLeft() { return{ mShipRect.x,mShipRect.y+mShipRect.h }; }
	static SDL_Point BottomRight() { return{ mShipRect.x + mShipRect.w,mShipRect.y + mShipRect.h }; }

	void Draw(SDL_Renderer* renderer);
	void Update(float delta);
};
