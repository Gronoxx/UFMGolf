#include "Level.h"

#include <utility>
#include "util/Consts.hpp"

Level::Level() {
    this->obstacles = std::make_unique<std::vector<std::shared_ptr<Obstacle>>>();
    this->Remaining_Moves = -1;
}


Level::Level(std::shared_ptr<Launcher> &l) {
    this->l = l;
    this->obstacles = std::make_unique<std::vector<std::shared_ptr<Obstacle>>>();
    this->Remaining_Moves = -1;
}

void Level::Dim_Moves() {
    this->Remaining_Moves--;
}

int Level::Get_Remaining_Moves() {
    return this->Remaining_Moves;
}

double Level::Get_Time() {
    return this->Time;
}

double Level::Get_pos_ball_init_x() {
    return this->pos_ball_init_x;
}

double Level::Get_pos_ball_init_y() {
    return this->pos_ball_init_y;
}

double Level::Get_pos_hole_init_x() {
    return this->pos_hole_init_x;
}

double Level::Get_pos_hole_init_y() {
    return this->pos_hole_init_y;
}

void Level::Set_Remaining_Moves(int Rem) {
    this->Remaining_Moves = Rem;
}

void Level::Set_Time(double Time) {
    this->Time = Time;
}

void Level::Set_pos_ball_init_x(double x) {
    this->pos_ball_init_x = x;
}

void Level::Set_pos_ball_init_y(double y) {
    this->pos_ball_init_y = y;
}

void Level::Set_pos_hole_init_x(double x) {
    this->pos_hole_init_x = x;
}

void Level::Set_pos_hole_init_y(double y) {
    this->pos_hole_init_y = y;
}


SDL_Renderer *Level::Get_Main_Launcher_Render() {
    return this->l->Get_Render();
}

std::shared_ptr<Launcher> Level::Get_Launcher() {
    return this->l;
}

bool Level::Get_Run() {
    return this->run;
}

bool *Level::Get_pRun() {
    return this->prun;
}

void Level::Set_Run(bool b) {
    this->run = b;
}

bool Level::Get_Stop() {
    return this->stop;
}

void Level::Set_Stop(bool s) {
    this->stop = s;
}

void Level::Add_Obstacle(SDL_Renderer *ren, SDL_Texture *Obs_Tx, int id, int x, int y, int w, int h) {
    this->obstacles->push_back(std::make_shared<Obstacle>(ren, Obs_Tx, id, x, y, w, h));
}


void Level::Render() {
    SDL_RenderClear(this->Get_Main_Launcher_Render());

    SDL_RenderCopy(
            this->Get_Main_Launcher_Render(),
            BG->Get_Tex(),
            nullptr,
            BG->Get_pRect()
    );
    SDL_RenderCopy(
            this->Get_Main_Launcher_Render(),
            hole->Get_Tex(),
            nullptr,
            hole->Get_pbrect()
    );

    for (const auto &obstacle: *this->obstacles)
        SDL_RenderCopy(this->Get_Main_Launcher_Render(), obstacle->Get_Tex(), nullptr, obstacle->Get_pbrect());

    this->ball->Render(this->Get_Main_Launcher_Render());

    SDL_RenderPresent(this->Get_Main_Launcher_Render());

}

void Level::Mover(double Var_x, double Var_y, bool *run) {

    if (this->Remaining_Moves != -1) this->Remaining_Moves--;
    //Maximo da Velocity
    double Velocity;
    if (sqrt(pow((Var_x), 2) + pow((Var_y), 2)) / 100 > 1)
        Velocity = 1;
    else
        Velocity = sqrt(pow((Var_x), 2) + pow((Var_y), 2)) / 100;
    //Normalização das Var's
    double holder_x = Var_x, holder_y = Var_y;
    int aux_x = 1, aux_y = 1;
    if (Var_x < 0) {
        aux_x = -1;
        Var_x = Var_x * -1;
    }
    if (Var_y < 0) {
        aux_y = -1;
        Var_y = Var_y * -1;
    }
    if (Var_x > Var_y) {
        Var_y = Var_y / Var_x;
        Var_x = 1;
    } else {
        Var_x = Var_x / Var_y;
        Var_y = 1;
    }
    if ((Var_x > 0 && aux_x < 0) || (Var_x < 0 && aux_x > 0))
        Var_x = Var_x * -1;
    if ((Var_y > 0 && aux_y < 0) || (Var_y < 0 && aux_y > 0))
        Var_y = Var_y * -1;

    while (Velocity > 0.001) {
        //garantir q n saia da tela
        if ((this->ball->Get_X() + Var_x * (75 * Velocity)) < 0 ||
            (this->ball->Get_X() + Var_x * (75 * Velocity)) + this->ball->Get_W() > WINDOW_WIDTH) {
            Var_x = Var_x * -1;
        }
        if ((this->ball->Get_Y() + Var_y * (75 * Velocity)) < 0 ||
            (this->ball->Get_Y() + Var_y * (75 * Velocity)) + this->ball->Get_H() > WINDOW_HEIGHT) {
            Var_y = Var_y * -1;
        }


        //garantir que não bate no obstaculo
        int holder_x = 0;
        int holder_y = 0;
        bool aux_atv = true;
        //Variação em X em sentido positivo(pela esquerda -> )
        if (Var_x > 0) {
            for (int count = 0; count < round(Var_x * (Velocity * 75)); count++) {
                for (const auto &obs: *this->obstacles) {
                    if (this->ball->Get_X() + count < obs->Get_X() + obs->Get_W() &&
                        this->ball->Get_X() + count + this->ball->Get_W() > obs->Get_X() &&
                        this->ball->Get_Y() < obs->Get_Y() + obs->Get_H() &&
                        this->ball->Get_H() + this->ball->Get_Y() > obs->Get_Y()) {

                        //Se ativar a batida pela esquerda não precisamos procurar nos outros lugares
                        aux_atv = false;
                        //alocando ultimo valor valido
                        this->ball->Set_X(this->ball->Get_X() + count - 1);
                        holder_x = count - 1;
                        this->ball->Set_Y(this->ball->Get_Y() + round(count * Var_y / Var_x));
                        holder_y = round(count * Var_y / Var_x);
                        Var_x = Var_x * -1;

                        //Delay entre frames
                        this->Render();
                        SDL_Delay(75);
                    }
                }
            }
        }
        if (aux_atv) {
            //Variação em X em sentido negativo (pela direita <-)
            if (Var_x < 0) {
                for (int count = 0; count > round(Var_x * (Velocity * 75)); count--) {
                    for (const auto &obs: *this->obstacles) {
                        if (this->ball->Get_X() + count < obs->Get_X() + obs->Get_W() &&
                            this->ball->Get_X() + count + this->ball->Get_W() > obs->Get_X() &&
                            this->ball->Get_Y() < obs->Get_Y() + obs->Get_H() &&
                            this->ball->Get_H() + this->ball->Get_Y() > obs->Get_Y()) {
                            //Se ativar a batida pela esquerda não precisamos procurar nos outros lugares
                            aux_atv = false;
                            //alocando ultimo valor valido
                            this->ball->Set_X(this->ball->Get_X() + count + 1);
                            holder_x = count +
                                       1;             //negativo , sinal de y , negativo, logo preservação de sinal de y
                            this->ball->Set_Y(this->ball->Get_Y() + round(count * Var_y / Var_x));
                            holder_y = round(count * Var_y / Var_x);
                            Var_x = Var_x * -1;

                            this->Render();
                            SDL_Delay(75);
                        }
                    }
                }
            }
        }
        if (aux_atv) {
            if (Var_y > 0) {
                for (int count = 0; count < round(Var_y * (Velocity * 75)); count++) {
                    for (const auto &obs: *this->obstacles) {
                        if (this->ball->Get_X() < obs->Get_X() + obs->Get_W() &&
                            this->ball->Get_X() + this->ball->Get_W() > obs->Get_X() &&
                            this->ball->Get_Y() + count < obs->Get_Y() + obs->Get_H() &&
                            this->ball->Get_H() + count + this->ball->Get_Y() > obs->Get_Y()) {

                            //Se ativar a batida pela esquerda não precisamos procurar nos outros lugares
                            aux_atv = false;
                            //alocando ultimo valor valido
                            this->ball->Set_Y(this->ball->Get_Y() + count - 1);
                            holder_y = count - 1;
                            this->ball->Set_X(this->ball->Get_X() + round(count * Var_x / Var_y));
                            holder_y = round(count * Var_x / Var_y);
                            Var_y = Var_y * -1;


                            this->Render();
                            SDL_Delay(75);
                        }
                    }
                }
            }
        }
        if (aux_atv) {
            if (Var_y < 0) {
                for (int count = 0; count > round(Var_y * (Velocity * 75)); count--) {
                    for (const auto &obs: *this->obstacles) {
                        if (this->ball->Get_X() < obs->Get_X() + obs->Get_W() &&
                            this->ball->Get_X() + this->ball->Get_W() > obs->Get_X() &&
                            this->ball->Get_Y() + count < obs->Get_Y() + obs->Get_H() &&
                            this->ball->Get_H() + count + this->ball->Get_Y() > obs->Get_Y()) {

                            //Se ativar a batida pela esquerda não precisamos procurar nos outros lugares
                            aux_atv = false;
                            //alocando ultimo valor valido
                            this->ball->Set_Y(this->ball->Get_Y() + count + 1);
                            holder_y = count + 1;
                            this->ball->Set_X(this->ball->Get_X() + round(count * Var_x / Var_y));
                            holder_y = round(count * Var_x / Var_y);
                            Var_y = Var_y * -1;
                            this->Render();
                            SDL_Delay(75);
                        }
                    }

                }
            }


        }

        this->ball->Set_X((this->ball->Get_X() + round(Var_x * (Velocity * 75)) - holder_x));
        this->ball->Set_Y((this->ball->Get_Y() + round(Var_y * (Velocity * 75)) - holder_y));
        //limpando a ultima impressão da bola, ou seja, reimprindo o fundo

        this->Render();
        SDL_Delay(75);
        //Bola no buraco
        if (hole->Ball_Presence(this->ball->Get_X(), this->ball->Get_Y(), Velocity)) {
            Velocity = 0;
            this->ball->Set_X(hole->Get_X());
            this->ball->Set_Y(hole->Get_Y());
            for (int count = this->ball->Get_W(); count >= 0; count--) {
                this->ball->Dim_Tam(1);
                // compensando a posição que é perdida com o decrescimo
                if (count % 2 == 0) {
                    this->ball->Set_X(this->ball->Get_X() + 1);
                    this->ball->Set_Y(this->ball->Get_Y() + 1);
                }
                this->Render();
                SDL_Delay(75);
            }
            *run = false;
            break;
        }
        this->ball->Gerar_Atrito(Velocity);

        if (this->Get_Remaining_Moves() == 0 && !this->ball->Get_In()) {
            this->Set_Run(false);
            this->Set_Stop(true);
            std::cout << "GAME OVER" << std::endl;
        }
    }

}

void Level::setLaucher(const std::shared_ptr<Launcher>& la) {
    this->l = la;
}

void Level::UpdateTimer() {
    if (timer != nullptr) {
        timer->Tick();
        timer->Reset();
        itime += timer->DeltaTime();


        if (itime >= 1.0f) {
            timer->Reset();
            current = itime + frames;
            std::cout << "Tempo Restante: " << this->Time - current << std::endl;
            itime = 0.0f;
            frames++;
        }

        if (current == this->Time) {
            this->Set_Run(false);
        }
    }
}

void Level::Set_Ball(std::unique_ptr<Ball> b) {
    this->ball = std::move(b);
}
void Level::Set_BackGround(std::unique_ptr<Background> b){
    this->BG = std::move(b);
}

void Level::Set_Hole(std::unique_ptr<Hole> h){
    this->hole = std::move(h);
}

void Level::Set_Timer() {
    this->timer = EngineUtils::Timer::Instance();
}

