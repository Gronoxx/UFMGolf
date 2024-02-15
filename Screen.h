#pragma once
#include <iostream>
#include <SDL_image.h>
#include <SDL.h>
class Screen
{
private:
	const int WIDTH = 1000, HEIGHT = 800;
	SDL_Window* window = SDL_CreateWindow("UFMGOLF", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
public:
	SDL_Window* Get_Window();
};
