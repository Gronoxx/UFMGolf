#pragma once
#include <iostream>
#include <SDL_image.h>
#include <SDL.h>
class Entity {
private:
	SDL_Rect* pbrect;
	SDL_Surface* Sur;
	SDL_Renderer* Ren;
	SDL_Texture* Tex;
	SDL_Rect brect;
public:
	void Set_W(int W);
	void Set_H(int H);
	void Set_X(int X);
	void Set_Y(int Y);
	void Set_Surface(SDL_Surface * Sur);
	void Set_Render(SDL_Renderer* Ren);
	void Set_Texture(SDL_Texture* Tex);
	void Set_pbrect();
	int Get_W();
	int Get_H();
	int Get_X();
	int Get_Y();
	SDL_Surface* Get_Surface();
	SDL_Renderer* Get_Render();
	SDL_Texture* Get_Tex();
	SDL_Rect* Get_pbrect();
	SDL_Rect& Get_brect_ref();
	
};
