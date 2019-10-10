#include "TextManager.h"

 TTF_Font*		TextManager::Font = nullptr;
 SDL_Surface*	TextManager::Message = nullptr;
 SDL_Texture*	TextManager::Text = nullptr;
 SDL_Rect		TextManager::DestRect;
 SDL_Color		TextManager::TextColor;

 bool TextManager::Load()
 {
	 TextColor = { 255,0,0,255 };
	 //TTF initialized
	 if (TTF_Init() == -1) {
		 std::cout << "Failed to Initialize TTF" << std::endl;
		 return false;
	 }

	 //load the font
	 Font = TTF_OpenFont("FreeSerif.ttf", 20);
	 if (Font == nullptr) {
		 std::cout << "Failed to get font" << std::endl;
		 return false;
	 }

	 return true;
 }

 void TextManager::DrawScore(SDL_Renderer * renderer, int score,int mScreenWidth)
 {
	 Font = TTF_OpenFont("FreeSerif.ttf", 18);
	 std::string scoreString = std::string("SCORE: " + std::to_string(score));
	 Message = TTF_RenderText_Solid(Font, scoreString.c_str(), TextColor);
	 Text = SDL_CreateTextureFromSurface(renderer, Message);

	 SDL_QueryTexture(Text, nullptr, nullptr, &DestRect.w, &DestRect.h);
	 DestRect.x = mScreenWidth / 2 - 100; DestRect.y = 15;

	 SDL_RenderCopyEx(renderer, Text, nullptr, &DestRect, 0, nullptr, SDL_FLIP_NONE);
 }

 void TextManager::DrawMissileCount(SDL_Renderer * renderer, Turret const * t)
 {
	 Font = TTF_OpenFont("FreeSerif.ttf", 20);
	 std::string missileCount = std::string( std::to_string(t->GetMissileCount()));
	 Message = TTF_RenderText_Solid(Font, missileCount.c_str(), TextColor);
	 Text = SDL_CreateTextureFromSurface(renderer, Message);

	 SDL_QueryTexture(Text, nullptr, nullptr, &DestRect.w, &DestRect.h);
	 DestRect.x = t->GetStartPostition().x - DestRect.w /2 ; DestRect.y = t->GetStartPostition().y + 10;

	 SDL_RenderCopyEx(renderer, Text, nullptr, &DestRect, 0, nullptr, SDL_FLIP_NONE);
 }

 void TextManager::DrawGameOver(SDL_Renderer * renderer, int mScreenWidth, int mScreenHeight)
 {
	 Font = TTF_OpenFont("FreeSerif.ttf", 25);
	 std::string GameOver = std::string("GAME OVER - PRESS \'R\' TO RESTART");
	 Message = TTF_RenderText_Solid(Font, GameOver.c_str(), TextColor);
	 Text = SDL_CreateTextureFromSurface(renderer, Message);

	 SDL_QueryTexture(Text, nullptr, nullptr, &DestRect.w, &DestRect.h);
	 DestRect.x = mScreenWidth / 2 - DestRect.w/2; DestRect.y = mScreenHeight/2;

	 SDL_RenderCopyEx(renderer, Text, nullptr, &DestRect, 0, nullptr, SDL_FLIP_NONE);
 }

 void TextManager::DrawNextLevelScreen(SDL_Renderer * renderer, int level,int mScreenWidth,int mScreenHeight)
 {
	 Font = TTF_OpenFont("FreeSerif.ttf", 25);
	 std::string GameOver = std::string("LEVEL - "+std::to_string(level));
	 Message = TTF_RenderText_Solid(Font, GameOver.c_str(), TextColor);
	 Text = SDL_CreateTextureFromSurface(renderer, Message);

	 SDL_QueryTexture(Text, nullptr, nullptr, &DestRect.w, &DestRect.h);
	 DestRect.x = mScreenWidth / 2 - DestRect.w / 2; DestRect.y = mScreenHeight / 2;

	 SDL_RenderCopyEx(renderer, Text, nullptr, &DestRect, 0, nullptr, SDL_FLIP_NONE);
 }
