#pragma once
#include <iostream>
#include <SDL_image.h>
#include <SDL.h>
class Background
{
private:
	SDL_Texture* BG_Tex;
	SDL_Surface* BG_Sur;
	SDL_Rect BG_Rect;
	SDL_Rect* p_BG_Rect;
public:
	Background(int BG_ID, SDL_Renderer* ren);
	SDL_Texture* Get_Tex();
	SDL_Surface* Get_Sur();
	SDL_Rect Get_Rect();
	SDL_Rect* Get_pRect();
};

