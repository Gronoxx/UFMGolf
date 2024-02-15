#include "Hole.h"
#include "util/Util.hpp"

const int margem_erro = 8;
Hole::Hole(SDL_Renderer* ren, SDL_Texture* Hole_Tx, double init_x_pos, double init_y_pos, const double hole_radius) {
	this->Set_H(hole_radius);
	this->Set_W(hole_radius);
	this->Set_X(init_x_pos);
	this->Set_Y(init_y_pos);
	this->Set_Render(ren);
	this->Set_Texture(Hole_Tx);
	this->Set_Surface(IMG_Load(("Imagens_Golf" + Util::getSeparator() + "Hole.png").c_str()));
	this->Set_pbrect();
}
void Hole::Aum_Tam(double Var_r) {
	this->Set_W(this->Get_W() + Var_r);
	this->Set_H(this->Get_H() + Var_r);
}
void Hole::Dim_Tam(double Var_r) {
	this->Set_W(this->Get_W() - Var_r);
	this->Set_H(this->Get_H() - Var_r);
}
bool Hole::Ball_Presence(double ball_x, double ball_y, double Velocity) {
	if (((ball_x - margem_erro) < this->Get_X() && this->Get_X() < (ball_x + margem_erro)) && ((ball_y - margem_erro) < this->Get_Y() && this->Get_Y() < (ball_y + margem_erro)) && Velocity <= 0.5)
		return true;
	else return false;
}