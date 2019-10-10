#include "City.h"

City::City()
{
}

City::City(SDL_Point start, int w, int h, bool active) :
	mCity({start.x,start.y,w,h}),
	mActive(active)
{

}

void City::Draw(SDL_Renderer * renderer) const
{
	SDL_SetRenderDrawColor(renderer, 150, 150, 180, 255);
	SDL_RenderFillRect(renderer, &mCity); 
	
	// Draw Yellow windows..
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	SDL_Rect windowTemp = { mCity.x + 5,mCity.y + 5,5,5 };
	SDL_RenderFillRect(renderer, &windowTemp);
	 windowTemp = { mCity.x + 15,mCity.y + 5,5,5 };
	SDL_RenderFillRect(renderer, &windowTemp);
	 windowTemp = { mCity.x + 5,mCity.y + 15,5,5 };
	SDL_RenderFillRect(renderer, &windowTemp);
	 windowTemp = { mCity.x + 15,mCity.y + 15,5,5 };
	SDL_RenderFillRect(renderer, &windowTemp);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
