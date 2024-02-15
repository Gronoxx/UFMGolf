#pragma once
#include "Entity.h"
class Obstacle :
	public Entity
{
public:
	Obstacle(SDL_Renderer* ren, SDL_Texture* Obs_Tx, int id, int x, int y, int w, int h);
	bool Ball_Presence_x(int x, int y, int radius);
	bool Ball_Presence_y(int x, int y, int radius);
};