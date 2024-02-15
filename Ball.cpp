
#include "Ball.h"
#include "util/Util.hpp"

const int WINDOW_WIDTH = 1000, WINDOW_HEIGHT = 800;
const double FRICTION = 0.02;
Ball::Ball(SDL_Renderer* ren, SDL_Texture* Ball_Tx, double init_x_pos, double init_y_pos, const double ball_radius) {
	this->Set_pbrect();
	this->Set_Render(ren);
	this->Set_Surface(IMG_Load(("Imagens_Golf" + Util::getSeparator() + "GolfBG.png").c_str()));
	this->Set_Texture(Ball_Tx);
	this->Set_X(init_x_pos);
	this->Set_Y(init_y_pos);
	this->Set_W(ball_radius);
	this->Set_H(ball_radius);
}

bool Ball::Get_In() {
	return this->in;
}
void Ball::Set_In(bool d) {
	this->in = d;
}

void Ball::Mover(Background* BG, Hole* hole, double Var_x, double Var_y, double Velocity, bool* run) {
	while (Velocity > 0.001) {

		//garantir q n saia da tela
		if ((this->Get_X() + Var_x * (75 * Velocity)) < 0 || (this->Get_X() + Var_x * (75 * Velocity)) + this->Get_W() > WINDOW_WIDTH)
		{
			Var_x = Var_x * -1;
		}
		if ((this->Get_Y() + Var_y * (75 * Velocity)) < 0 || (this->Get_Y() + Var_y * (75 * Velocity)) + this->Get_H() > WINDOW_HEIGHT)
		{
			Var_y = Var_y * -1;
		}
		//altera a posição da bola de acordo com a velocidade atual
		this->Set_X((this->Get_X() + round(Var_x * (Velocity * 75))));
		this->Set_Y((this->Get_Y() + round(Var_y * (Velocity * 75))));
		//limpando a ultima impressão da bola, ou seja, reimprindo o fundo

		SDL_Delay(75);
		//Bola no buraco
		if (hole->Ball_Presence(this->Get_X(), this->Get_Y(), Velocity)) {
			Velocity = 0;
			this->Set_X(hole->Get_X());
			this->Set_Y(hole->Get_Y());
			for (int count = this->Get_W(); count >= 0; count--) {
				this->Dim_Tam(1);
				// compensando a posição que é perdida com o decrescimo
				if (count % 2 == 0) {
					this->Set_X(this->Get_X() + 1);
					this->Set_Y(this->Get_Y() + 1);
				}

				SDL_Delay(75);
				this->Set_In(true);
			}
			*run = false;
			break;
		}

		Gerar_Atrito(Velocity);

	}
}
void Ball::Gerar_Atrito(double& Velocity) {
	Velocity = Velocity - FRICTION;
}
void Ball::Aum_Tam(int Var_r) {
	this->Set_W(this->Get_W() + Var_r);
	this->Set_H(this->Get_H() + Var_r);
}
void Ball::Dim_Tam(int Var_r) {
	this->Set_W(this->Get_W() - Var_r);
	this->Set_H(this->Get_H() - Var_r);
}

void Ball::Render(SDL_Renderer * render) {
    SDL_RenderCopy(render, this->Get_Tex(), NULL, this->Get_pbrect());
}

void Ball::Mover(Background* BG, Hole* hole, double Var_x, double Var_y, double Velocity, bool* run, Obstacle* obs, Obstacle* obs_1, Obstacle* obs_2, Obstacle* obs_3) {
	while (Velocity > 0.001) {
		//garantir q n saia da tela
		if ((this->Get_X() + Var_x * (75 * Velocity)) < 0 || (this->Get_X() + Var_x * (75 * Velocity)) + this->Get_W() > WINDOW_WIDTH)
		{
			Var_x = Var_x * -1;
		}
		if ((this->Get_Y() + Var_y * (75 * Velocity)) < 0 || (this->Get_Y() + Var_y * (75 * Velocity)) + this->Get_H() > WINDOW_HEIGHT)
		{
			Var_y = Var_y * -1;
		}


		//garantir que não bate no obstaculo
		int holder_x = 0;
		int holder_y = 0;
		bool aux_atv = true;
		//Variação em X em sentido positivo(pela esquerda -> )
		if (Var_x > 0) {
			for (int count = 0; count < round(Var_x * (Velocity * 75)); count++)
			{
				if (this->Get_X() + count < obs->Get_X() + obs->Get_W() &&
					this->Get_X() + count + this->Get_W() > obs->Get_X() &&
					this->Get_Y() < obs->Get_Y() + obs->Get_H() &&
					this->Get_H() + this->Get_Y() > obs->Get_Y())
				{

					//Se ativar a batida pela esquerda não precisamos procurar nos outros lugares
					aux_atv = false;
					//alocando ultimo valor valido
					this->Set_X(this->Get_X() + count - 1);
					holder_x = count - 1;
					this->Set_Y(this->Get_Y() + round(count * Var_y / Var_x));
					holder_y = round(count * Var_y / Var_x);
					Var_x = Var_x * -1;


					//Delay entre frames
					SDL_Delay(75);
				}
			}
		}
		if (aux_atv) {
			//Variação em X em sentido negativo (pela direita <-)
			if (Var_x < 0)
			{
				for (int count = 0; count > round(Var_x * (Velocity * 75)); count--)
				{
					if (this->Get_X() + count < obs->Get_X() + obs->Get_W() &&
						this->Get_X() + count + this->Get_W() > obs->Get_X() &&
						this->Get_Y() < obs->Get_Y() + obs->Get_H() &&
						this->Get_H() + this->Get_Y() > obs->Get_Y())
					{
						//Se ativar a batida pela esquerda não precisamos procurar nos outros lugares
						aux_atv = false;
						//alocando ultimo valor valido
						this->Set_X(this->Get_X() + count + 1);
						holder_x = count + 1;             //negativo , sinal de y , negativo, logo preservação de sinal de y
						this->Set_Y(this->Get_Y() + round(count * Var_y / Var_x));
						holder_y = round(count * Var_y / Var_x);
						Var_x = Var_x * -1;

						SDL_Delay(75);
					}
				}
			}
		}
		if (aux_atv) {
			if (Var_y > 0) {
				for (int count = 0; count < round(Var_y * (Velocity * 75)); count++)
				{
					if (this->Get_X() < obs->Get_X() + obs->Get_W() &&
						this->Get_X() + this->Get_W() > obs->Get_X() &&
						this->Get_Y() + count < obs->Get_Y() + obs->Get_H() &&
						this->Get_H() + count + this->Get_Y() > obs->Get_Y())
					{

						//Se ativar a batida pela esquerda não precisamos procurar nos outros lugares
						aux_atv = false;
						//alocando ultimo valor valido
						this->Set_Y(this->Get_Y() + count - 1);
						holder_y = count - 1;
						this->Set_X(this->Get_X() + round(count * Var_x / Var_y));
						holder_y = round(count * Var_x / Var_y);
						Var_y = Var_y * -1;
						SDL_Delay(75);

					}
				}
			}
		}
		if (aux_atv) {
			if (Var_y < 0) {
				for (int count = 0; count > round(Var_y * (Velocity * 75)); count--)
				{
					if (this->Get_X() < obs->Get_X() + obs->Get_W() &&
						this->Get_X() + this->Get_W() > obs->Get_X() &&
						this->Get_Y() + count < obs->Get_Y() + obs->Get_H() &&
						this->Get_H() + count + this->Get_Y() > obs->Get_Y())
					{

						//Se ativar a batida pela esquerda não precisamos procurar nos outros lugares
						aux_atv = false;
						//alocando ultimo valor valido
						this->Set_Y(this->Get_Y() + count + 1);
						holder_y = count + 1;
						this->Set_X(this->Get_X() + round(count * Var_x / Var_y));
						holder_y = round(count * Var_x / Var_y);
						Var_y = Var_y * -1;
					}
				}
			}



		}

		//-----------------------------------------------
		//Variação em X em sentido positivo(pela esquerda -> )
		if (Var_x > 0) {
			for (int count = 0; count < round(Var_x * (Velocity * 75)); count++)
			{
				if (this->Get_X() + count < obs_1->Get_X() + obs_1->Get_W() &&
					this->Get_X() + count + this->Get_W() > obs_1->Get_X() &&
					this->Get_Y() < obs_1->Get_Y() + obs_1->Get_H() &&
					this->Get_H() + this->Get_Y() > obs_1->Get_Y())
				{

					//Se ativar a batida pela esquerda não precisamos procurar nos outros lugares
					aux_atv = false;
					//alocando ultimo valor valido
					this->Set_X(this->Get_X() + count - 1);
					holder_x = count - 1;
					this->Set_Y(this->Get_Y() + round(count * Var_y / Var_x));
					holder_y = round(count * Var_y / Var_x);
					Var_x = Var_x * -1;

					//Delay entre frames
					SDL_Delay(75);
				}
			}
		}
		if (aux_atv) {
			//Variação em X em sentido negativo (pela direita <-)
			if (Var_x < 0)
			{
				for (int count = 0; count > round(Var_x * (Velocity * 75)); count--)
				{
					if (this->Get_X() + count < obs_1->Get_X() + obs_1->Get_W() &&
						this->Get_X() + count + this->Get_W() > obs_1->Get_X() &&
						this->Get_Y() < obs_1->Get_Y() + obs_1->Get_H() &&
						this->Get_H() + this->Get_Y() > obs_1->Get_Y())
					{
						//Se ativar a batida pela esquerda não precisamos procurar nos outros lugares
						aux_atv = false;
						//alocando ultimo valor valido
						this->Set_X(this->Get_X() + count + 1);
						holder_x = count + 1;             //negativo , sinal de y , negativo, logo preservação de sinal de y
						this->Set_Y(this->Get_Y() + round(count * Var_y / Var_x));
						holder_y = round(count * Var_y / Var_x);
						Var_x = Var_x * -1;

						//Delay entre frames
						SDL_Delay(75);
					}
				}
			}
		}
		if (aux_atv) {
			if (Var_y > 0) {
				for (int count = 0; count < round(Var_y * (Velocity * 75)); count++)
				{
					if (this->Get_X() < obs_1->Get_X() + obs_1->Get_W() &&
						this->Get_X() + this->Get_W() > obs_1->Get_X() &&
						this->Get_Y() + count < obs_1->Get_Y() + obs_1->Get_H() &&
						this->Get_H() + count + this->Get_Y() > obs_1->Get_Y())
					{

						//Se ativar a batida pela esquerda não precisamos procurar nos outros lugares
						aux_atv = false;
						//alocando ultimo valor valido
						this->Set_Y(this->Get_Y() + count - 1);
						holder_y = count - 1;
						this->Set_X(this->Get_X() + round(count * Var_x / Var_y));
						holder_y = round(count * Var_x / Var_y);
						Var_y = Var_y * -1;

						SDL_Delay(75);

					}
				}
			}
		}
		if (aux_atv) {
			if (Var_y < 0) {
				for (int count = 0; count > round(Var_y * (Velocity * 75)); count--)
				{
					if (this->Get_X() < obs_1->Get_X() + obs_1->Get_W() &&
						this->Get_X() + this->Get_W() > obs_1->Get_X() &&
						this->Get_Y() + count < obs_1->Get_Y() + obs_1->Get_H() &&
						this->Get_H() + count + this->Get_Y() > obs_1->Get_Y())
					{

						//Se ativar a batida pela esquerda não precisamos procurar nos outros lugares
						aux_atv = false;
						//alocando ultimo valor valido
						this->Set_Y(this->Get_Y() + count + 1);
						holder_y = count + 1;
						this->Set_X(this->Get_X() + round(count * Var_x / Var_y));
						holder_y = round(count * Var_x / Var_y);
						Var_y = Var_y * -1;
					}
				}
			}



		}

		//-----------------------------------------------
		//Variação em X em sentido positivo(pela esquerda -> )
		if (Var_x > 0) {
			for (int count = 0; count < round(Var_x * (Velocity * 75)); count++)
			{
				if (this->Get_X() + count < obs_2->Get_X() + obs_2->Get_W() &&
					this->Get_X() + count + this->Get_W() > obs_2->Get_X() &&
					this->Get_Y() < obs_2->Get_Y() + obs_2->Get_H() &&
					this->Get_H() + this->Get_Y() > obs_2->Get_Y())
				{

					//Se ativar a batida pela esquerda não precisamos procurar nos outros lugares
					aux_atv = false;
					//alocando ultimo valor valido
					this->Set_X(this->Get_X() + count - 1);
					holder_x = count - 1;
					this->Set_Y(this->Get_Y() + round(count * Var_y / Var_x));
					holder_y = round(count * Var_y / Var_x);
					Var_x = Var_x * -1;

					SDL_Delay(75);
				}
			}
		}
		if (aux_atv) {
			//Variação em X em sentido negativo (pela direita <-)
			if (Var_x < 0)
			{
				for (int count = 0; count > round(Var_x * (Velocity * 75)); count--)
				{
					if (this->Get_X() + count < obs_2->Get_X() + obs_2->Get_W() &&
						this->Get_X() + count + this->Get_W() > obs_2->Get_X() &&
						this->Get_Y() < obs_2->Get_Y() + obs_2->Get_H() &&
						this->Get_H() + this->Get_Y() > obs_2->Get_Y())
					{
						//Se ativar a batida pela esquerda não precisamos procurar nos outros lugares
						aux_atv = false;
						//alocando ultimo valor valido
						this->Set_X(this->Get_X() + count + 1);
						holder_x = count + 1;             //negativo , sinal de y , negativo, logo preservação de sinal de y
						this->Set_Y(this->Get_Y() + round(count * Var_y / Var_x));
						holder_y = round(count * Var_y / Var_x);
						Var_x = Var_x * -1;

						SDL_Delay(75);
					}
				}
			}
		}
		if (aux_atv) {
			if (Var_y > 0) {
				for (int count = 0; count < round(Var_y * (Velocity * 75)); count++)
				{
					if (this->Get_X() < obs_2->Get_X() + obs_2->Get_W() &&
						this->Get_X() + this->Get_W() > obs_2->Get_X() &&
						this->Get_Y() + count < obs_2->Get_Y() + obs_2->Get_H() &&
						this->Get_H() + count + this->Get_Y() > obs_2->Get_Y())
					{

						//Se ativar a batida pela esquerda não precisamos procurar nos outros lugares
						aux_atv = false;
						//alocando ultimo valor valido
						this->Set_Y(this->Get_Y() + count - 1);
						holder_y = count - 1;
						this->Set_X(this->Get_X() + round(count * Var_x / Var_y));
						holder_y = round(count * Var_x / Var_y);
						Var_y = Var_y * -1;

						//Delay entre frames
						SDL_Delay(75);

					}
				}
			}
		}
		if (aux_atv) {
			if (Var_y < 0) {
				for (int count = 0; count > round(Var_y * (Velocity * 75)); count--)
				{
					if (this->Get_X() < obs_2->Get_X() + obs_2->Get_W() &&
						this->Get_X() + this->Get_W() > obs_2->Get_X() &&
						this->Get_Y() + count < obs_2->Get_Y() + obs_2->Get_H() &&
						this->Get_H() + count + this->Get_Y() > obs_2->Get_Y())
					{

						//Se ativar a batida pela esquerda não precisamos procurar nos outros lugares
						aux_atv = false;
						//alocando ultimo valor valido
						this->Set_Y(this->Get_Y() + count + 1);
						holder_y = count + 1;
						this->Set_X(this->Get_X() + round(count * Var_x / Var_y));
						holder_y = round(count * Var_x / Var_y);
						Var_y = Var_y * -1;
					}
				}
			}



		}

		//-----------------------------------------------
		//Variação em X em sentido positivo(pela esquerda -> )
		if (Var_x > 0) {
			for (int count = 0; count < round(Var_x * (Velocity * 75)); count++)
			{
				if (this->Get_X() + count < obs_3->Get_X() + obs_3->Get_W() &&
					this->Get_X() + count + this->Get_W() > obs_3->Get_X() &&
					this->Get_Y() < obs_3->Get_Y() + obs_3->Get_H() &&
					this->Get_H() + this->Get_Y() > obs_3->Get_Y())
				{

					//Se ativar a batida pela esquerda não precisamos procurar nos outros lugares
					aux_atv = false;
					//alocando ultimo valor valido
					this->Set_X(this->Get_X() + count - 1);
					holder_x = count - 1;
					this->Set_Y(this->Get_Y() + round(count * Var_y / Var_x));
					holder_y = round(count * Var_y / Var_x);
					Var_x = Var_x * -1;

					//Delay entre frames
					SDL_Delay(75);
				}
			}
		}
		if (aux_atv) {
			//Variação em X em sentido negativo (pela direita <-)
			if (Var_x < 0)
			{
				for (int count = 0; count > round(Var_x * (Velocity * 75)); count--)
				{
					if (this->Get_X() + count < obs_3->Get_X() + obs_3->Get_W() &&
						this->Get_X() + count + this->Get_W() > obs_3->Get_X() &&
						this->Get_Y() < obs_3->Get_Y() + obs_3->Get_H() &&
						this->Get_H() + this->Get_Y() > obs_3->Get_Y())
					{
						//Se ativar a batida pela esquerda não precisamos procurar nos outros lugares
						aux_atv = false;
						//alocando ultimo valor valido
						this->Set_X(this->Get_X() + count + 1);
						holder_x = count + 1;             //negativo , sinal de y , negativo, logo preservação de sinal de y
						this->Set_Y(this->Get_Y() + round(count * Var_y / Var_x));
						holder_y = round(count * Var_y / Var_x);
						Var_x = Var_x * -1;
						SDL_Delay(75);
					}
				}
			}
		}
		if (aux_atv) {
			if (Var_y > 0) {
				for (int count = 0; count < round(Var_y * (Velocity * 75)); count++)
				{
					if (this->Get_X() < obs_3->Get_X() + obs_3->Get_W() &&
						this->Get_X() + this->Get_W() > obs_3->Get_X() &&
						this->Get_Y() + count < obs_3->Get_Y() + obs_3->Get_H() &&
						this->Get_H() + count + this->Get_Y() > obs_3->Get_Y())
					{

						//Se ativar a batida pela esquerda não precisamos procurar nos outros lugares
						aux_atv = false;
						//alocando ultimo valor valido
						this->Set_Y(this->Get_Y() + count - 1);
						holder_y = count - 1;
						this->Set_X(this->Get_X() + round(count * Var_x / Var_y));
						holder_y = round(count * Var_x / Var_y);
						Var_y = Var_y * -1;

						//Delay entre frames
						SDL_Delay(75);

					}
				}
			}
		}
		if (aux_atv) {
			if (Var_y < 0) {
				for (int count = 0; count > round(Var_y * (Velocity * 75)); count--)
				{
					if (this->Get_X() < obs_3->Get_X() + obs_3->Get_W() &&
						this->Get_X() + this->Get_W() > obs_3->Get_X() &&
						this->Get_Y() + count < obs_3->Get_Y() + obs_3->Get_H() &&
						this->Get_H() + count + this->Get_Y() > obs_3->Get_Y())
					{

						//Se ativar a batida pela esquerda não precisamos procurar nos outros lugares
						aux_atv = false;
						//alocando ultimo valor valido
						this->Set_Y(this->Get_Y() + count + 1);
						holder_y = count + 1;
						this->Set_X(this->Get_X() + round(count * Var_x / Var_y));
						holder_y = round(count * Var_x / Var_y);
						Var_y = Var_y * -1;
					}
				}
			}



		}

		this->Set_X((this->Get_X() + round(Var_x * (Velocity * 75)) - holder_x));
		this->Set_Y((this->Get_Y() + round(Var_y * (Velocity * 75)) - holder_y));
		//limpando a ultima impressão da bola, ou seja, reimprindo o fundo

		SDL_Delay(75);
		//Bola no buraco
		if (hole->Ball_Presence(this->Get_X(), this->Get_Y(), Velocity)) {
			Velocity = 0;
			this->Set_X(hole->Get_X());
			this->Set_Y(hole->Get_Y());
			for (int count = this->Get_W(); count >= 0; count--) {
				this->Dim_Tam(1);
				// compensando a posição que é perdida com o decrescimo
				if (count % 2 == 0) {
					this->Set_X(this->Get_X() + 1);
					this->Set_Y(this->Get_Y() + 1);
				}

				SDL_Delay(75);
			}
			*run = false;
			break;
		}
		Gerar_Atrito(Velocity);
	}
}
