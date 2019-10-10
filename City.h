#pragma once
#include<SDL.h>

class City{
private:
	bool mActive;
	SDL_Rect mCity;

public:

	City();
	City(SDL_Point start, int w, int h, bool active);
	void Draw(SDL_Renderer*) const;
	bool IsActive() { return mActive; }
	void SetActive(bool active) { mActive = active; }
	
	int GetWidth() { return mCity.w; }
	int GetHeight() { return mCity.h; }
	SDL_Point GetPosition() { return { mCity.x + mCity.w / 2 ,mCity.y }; }
};