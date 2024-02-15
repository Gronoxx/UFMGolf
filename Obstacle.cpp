#include "Obstacle.h"
Obstacle::Obstacle(SDL_Renderer* ren, SDL_Texture* Obs_Tx, int id, int x, int y, int w, int h) {

	this->Set_pbrect();
	this->Set_X(x);
	this->Set_Y(y);
	this->Set_Render(ren);
	this->Set_Texture(Obs_Tx);
	this->Set_W(w);
	this->Set_H(h);
	switch (id) {
	case 0:
		this->Set_Surface(IMG_Load("Imagens_Golf/Obs.png"));
	case 1:
		this->Set_Surface(IMG_Load("Imagens_Golf/Obs.png"));
	case 2:
		this->Set_Surface(IMG_Load("Imagens_Golf/Obs.png"));
	case 3:
		this->Set_Surface(IMG_Load("Imagens_Golf/Obs.png"));
	}

}
bool Obstacle::Ball_Presence_x(int x, int y, int radius) {
	//std::cout << "Obstacle x: " << this->Get_X() << "  Obstacle y: " << this->Get_Y() << "Obstacle w: " << this->Get_W() << "  Obstacle h: " << this->Get_H() << std::endl;
	//std::cout << "Ball x: " << x << "  Ball y: " << y << "Ball w: " << radius << "  Ball h: " << radius << std::endl;
	//vindo pela esquerda
	if (((this->Get_X() == x + radius && (y >= this->Get_Y() && y <= (this->Get_Y() + this->Get_H())))))
		return true;
	//vindo pela direita
	else if (((x >= 400 && x <= 464) && (y >= 400 && y <= 464)))
		return true;
	else
		return false;
}
bool Obstacle::Ball_Presence_y(int x, int y, int radius) {
	if (((this->Get_Y() == y + radius && (x >= this->Get_X() && x <= (this->Get_X() + this->Get_W())))))
		return true;
	else if (((this->Get_Y() + this->Get_H() == y + radius && (x >= this->Get_X() && x <= (this->Get_X() + this->Get_H())))))
		return true;
	else
		return false;
}