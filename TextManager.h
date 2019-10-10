#pragma once
#include<SDL.h>
#include <SDL_ttf.h>
#include<string>
#include<iostream>
#include "Turret.h"

class TextManager {
private:
	static TTF_Font*		Font;
	static SDL_Surface*		Message;
	static SDL_Texture*		Text;
	static SDL_Rect			DestRect;
	static SDL_Color		TextColor;
public:
	static bool Load();

	static void DrawScore(SDL_Renderer* renderer,int score,int mScreenWidth);
	static void DrawMissileCount(SDL_Renderer* renderer, Turret const*);
	static void DrawGameOver(SDL_Renderer* renderer, int mScreenWidth, int mScreenHeight);
	static void DrawNextLevelScreen(SDL_Renderer* renderer,int level,int,int);

};