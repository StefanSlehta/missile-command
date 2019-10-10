#include <iostream>
#include "Game.h"
#include <math.h>

void Game::ProcessEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT:
			OnQuit();
			break;
		case SDL_KEYDOWN:
			OnKeyDown(&e.key);
			break;
		case SDL_KEYUP:
			OnKeyUp(&e.key);
			break;
		case SDL_MOUSEBUTTONDOWN:
			OnMouseDown(&e.button);
			break;
		case SDL_MOUSEBUTTONUP:
			OnMouseUp(&e.button);
			break;
		case SDL_MOUSEMOTION:
			OnMouseMotion(&e.motion);
			break;
		case SDL_WINDOWEVENT:
			break;
		default:
			break;
		}
	}
}

void Game::OnQuit()
{
	mShouldQuit = true;
}

void Game::OnWindowResized(int w, int h)
{
}

void Game::OnKeyDown(const SDL_KeyboardEvent * kbe)
{
	
	if (kbe->keysym.sym == SDLK_a)
		mSelectedTurret = &mTurrets[0];
	if (kbe->keysym.sym == SDLK_s)
		mSelectedTurret = &mTurrets[1];
	if (kbe->keysym.sym == SDLK_d)
		mSelectedTurret = &mTurrets[2];
	if (kbe->keysym.sym == SDLK_r && GameOver())
		Load();
}

void Game::OnKeyUp(const SDL_KeyboardEvent * kbe)
{
}

void Game::OnMouseDown(const SDL_MouseButtonEvent * mbe)
{

}

void Game::OnMouseUp(const SDL_MouseButtonEvent * mbe)
{
	if (mbe->y < mTurrets[0].GetStartPostition().y - 10) // don't wanna go under the turret with the marker
	{
		mMousePosition.x = mbe->x;
		mMousePosition.y = mbe->y;
	}

	if (mSelectedTurret == nullptr || !mSelectedTurret->CanFire())
		return;

	SDL_Point position = mSelectedTurret->GetStartPostition();
	double slope = atan2(mMousePosition.y - position.y , mMousePosition.x - position.x);
	SpawnMissile(false, &mMousePosition,false);
	mSelectedTurret->Fire();
}

void Game::OnMouseMotion(const SDL_MouseMotionEvent * mme)
{
	if (mme->y >= mTurrets[0].GetStartPostition().y-10) // don't wanna go under the turret with the marker
		return;

	mMousePosition.x = mme->x;
	mMousePosition.y = mme->y;

	if (mSelectedTurret == nullptr || !mSelectedTurret->IsActive())
		return;
	
	SDL_Point position = mSelectedTurret->GetStartPostition();
	mSelectedTurret->Face(atan2(position.y - mMousePosition.y, mMousePosition.x - position.x));
}

void Game::DrawMarker()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
	SDL_RenderDrawLine(mRenderer, mMousePosition.x - 8, mMousePosition.y - 8, mMousePosition.x + 8, mMousePosition.y + 8);
	SDL_RenderDrawLine(mRenderer, mMousePosition.x - 8, mMousePosition.y + 8, mMousePosition.x + 8, mMousePosition.y - 8);
}
