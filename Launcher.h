#pragma once
#include <iostream>
#include <SDL_image.h>
#include <SDL.h>
#include "Screen.h"
class Launcher
{
private:
	Screen Main_Screen;
	SDL_Surface* screen;
	SDL_Renderer* ren;
public:
	Launcher();
	SDL_Renderer* Get_Render();
	Screen Get_Screen();
};
