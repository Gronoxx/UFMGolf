#pragma once
#include "Entity.h"
class Hole :
    public Entity
{
public:
    Hole(SDL_Renderer* ren, SDL_Texture* Hole_Tx, double init_x_pos, double init_y_pos, const double hole_radius);
    void Dim_Tam(double Var_r);
    void Aum_Tam(double Var_r);
    bool Ball_Presence(double ball_x, double ball_y, double Velocity);
};