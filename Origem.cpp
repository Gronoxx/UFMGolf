#include <iostream>
#include <SDL_image.h>
#include <SDL.h>
#include "Launcher.h"
#include "Level.h"
#include "util/Util.hpp"

std::vector<std::unique_ptr<Level>> initialize_levels() {
    std::vector<std::unique_ptr<Level>> levels;
    auto laucher = std::make_shared<Launcher>();
    auto level_1 = std::make_unique<Level>(laucher);
    level_1->Set_pos_ball_init_x(100);
    level_1->Set_pos_ball_init_y(400);
    level_1->Set_pos_hole_init_x(575);
    level_1->Set_pos_hole_init_y(120);
    level_1->Set_Ball(std::make_unique<Ball>(level_1->Get_Main_Launcher_Render(),
                                             SDL_CreateTextureFromSurface(level_1->Get_Main_Launcher_Render(),
                                                                          IMG_Load(("Imagens_Golf" +
                                                                                    Util::getSeparator() +
                                                                                    "GolfBall.png").c_str())),
                                             level_1->Get_pos_ball_init_x(),
                                             level_1->Get_pos_ball_init_y(), 15));

    level_1->Set_Hole(std::make_unique<Hole>(level_1->Get_Main_Launcher_Render(),
                                             SDL_CreateTextureFromSurface(level_1->Get_Main_Launcher_Render(),
                                                                          IMG_Load(("Imagens_Golf" +
                                                                                    Util::getSeparator() +
                                                                                    "Hole.png").c_str())),
                                             level_1->Get_pos_hole_init_x(), level_1->Get_pos_hole_init_y(), 15));
    level_1->Set_BackGround(std::make_unique<Background>(0, level_1->Get_Main_Launcher_Render()));
    level_1->Set_Remaining_Moves(5);
    level_1->Render();

    levels.push_back(std::move(level_1));

    auto level_2 = std::make_unique<Level>(laucher);
    level_2->Set_pos_ball_init_x(100);
    level_2->Set_pos_ball_init_y(100);
    level_2->Set_pos_hole_init_x(500);
    level_2->Set_pos_hole_init_y(500);
    level_2->Set_Ball(std::make_unique<Ball>(level_2->Get_Main_Launcher_Render(),
                                             SDL_CreateTextureFromSurface(level_2->Get_Main_Launcher_Render(),
                                                                          IMG_Load("Imagens_Golf/GolfBall.png")),
                                             level_2->Get_pos_ball_init_x(),
                                             level_2->Get_pos_ball_init_y(), 15));

    level_2->Set_Hole(std::make_unique<Hole>(level_2->Get_Main_Launcher_Render(),
                                             SDL_CreateTextureFromSurface(level_2->Get_Main_Launcher_Render(),
                                                                          IMG_Load("Imagens_Golf/Hole.png")),
                                             level_2->Get_pos_hole_init_x(), level_2->Get_pos_hole_init_y(), 15));

    level_2->Set_BackGround(std::make_unique<Background>(0, level_2->Get_Main_Launcher_Render()));

    level_2->Add_Obstacle(
            level_2->Get_Main_Launcher_Render(),
            SDL_CreateTextureFromSurface(level_2->Get_Main_Launcher_Render(),
                                         IMG_Load("Imagens_Golf/Obs.png")),
            0, 200, 200, 32, 32);

    level_2->Add_Obstacle(level_2->Get_Main_Launcher_Render(),
                          SDL_CreateTextureFromSurface(level_2->Get_Main_Launcher_Render(),
                                                       IMG_Load("Imagens_Golf/Obs2.png")),
                          2, 400, 400, 64, 64);

    level_2->Add_Obstacle(level_2->Get_Main_Launcher_Render(),
                          SDL_CreateTextureFromSurface(level_2->Get_Main_Launcher_Render(),
                                                       IMG_Load("Imagens_Golf/Obs1.png")),
                          1, 600, 600, 32, 32);

    level_2->Add_Obstacle(level_2->Get_Main_Launcher_Render(),
                          SDL_CreateTextureFromSurface(level_2->Get_Main_Launcher_Render(),
                                                       IMG_Load("Imagens_Golf/Obs3.png")),
                          3, 650, 200, 64, 64);

    level_2->Set_Remaining_Moves(8);

    levels.push_back(std::move(level_2));

    auto level_3 = std::make_unique<Level>(laucher);

    level_3->Set_pos_ball_init_x(150);
    level_3->Set_pos_ball_init_y(400);
    level_3->Set_pos_hole_init_x(900);
    level_3->Set_pos_hole_init_y(400);
    level_3->Set_Ball( std::make_unique<Ball>(level_3->Get_Main_Launcher_Render(),
                                        SDL_CreateTextureFromSurface(level_3->Get_Main_Launcher_Render(),
                                                                     IMG_Load("Imagens_Golf/GolfBall.png")),
                                        level_3->Get_pos_ball_init_x(),
                                        level_3->Get_pos_ball_init_y(), 15));

    level_3->Set_Hole( std::make_unique<Hole>(level_3->Get_Main_Launcher_Render(),
                                        SDL_CreateTextureFromSurface(level_3->Get_Main_Launcher_Render(),
                                                                     IMG_Load("Imagens_Golf/Hole.png")),
                                        level_3->Get_pos_hole_init_x(), level_3->Get_pos_hole_init_y(), 15));

    level_3->Set_BackGround( std::make_unique<Background>(0, level_3->Get_Main_Launcher_Render()));

    level_3->Add_Obstacle(level_3->Get_Main_Launcher_Render(), SDL_CreateTextureFromSurface(level_3->Get_Main_Launcher_Render(),
                                                                                      IMG_Load(
                                                                                              "Imagens_Golf/Obs2.png")),
                       2, 286, 336, 128, 128);
    level_3->Add_Obstacle(level_3->Get_Main_Launcher_Render(), SDL_CreateTextureFromSurface(level_3->Get_Main_Launcher_Render(),
                                                                                      IMG_Load(
                                                                                              "Imagens_Golf/Obs3.png")),
                       3, 436, 50, 128, 128);
    level_3->Add_Obstacle(level_3->Get_Main_Launcher_Render(), SDL_CreateTextureFromSurface(level_3->Get_Main_Launcher_Render(),
                                                                                      IMG_Load(
                                                                                              "Imagens_Golf/Obs3.png")),
                       3, 436, 622, 128, 128);
    level_3->Add_Obstacle(level_3->Get_Main_Launcher_Render(), SDL_CreateTextureFromSurface(level_3->Get_Main_Launcher_Render(),
                                                                                      IMG_Load(
                                                                                              "Imagens_Golf/Obs2.png")),
                       2, 586, 336, 128, 128);

    level_3->Set_Remaining_Moves(10);

    levels.push_back(std::move(level_3));

    auto level_4 = std::make_unique<Level>(laucher);

    level_4->Set_pos_ball_init_x(150);
    level_4->Set_pos_ball_init_y(365);
    level_4->Set_pos_hole_init_x(492);
    level_4->Set_pos_hole_init_y(365);
    level_4->Set_Ball( std::make_unique<Ball>(level_4->Get_Main_Launcher_Render(),
                                        SDL_CreateTextureFromSurface(level_4->Get_Main_Launcher_Render(),
                                                                     IMG_Load("Imagens_Golf/GolfBall.png")),
                                        level_4->Get_pos_ball_init_x(),
                                        level_4->Get_pos_ball_init_y(), 15));

    level_4->Set_Hole(  std::make_unique<Hole>(level_4->Get_Main_Launcher_Render(),
                                        SDL_CreateTextureFromSurface(level_4->Get_Main_Launcher_Render(),
                                                                     IMG_Load("Imagens_Golf/Hole.png")),
                                        level_4->Get_pos_hole_init_x(), level_4->Get_pos_hole_init_y(), 15));

    level_4->Set_BackGround( std::make_unique<Background>(0, level_4->Get_Main_Launcher_Render()));


    level_4->Add_Obstacle(level_4->Get_Main_Launcher_Render(),
                       SDL_CreateTextureFromSurface(level_4->Get_Main_Launcher_Render(),
                                                    IMG_Load("Imagens_Golf/Obs1.png")),
                       0, 534, 357, 32, 32);
    level_4->Add_Obstacle(level_4->Get_Main_Launcher_Render(),
                       SDL_CreateTextureFromSurface(level_4->Get_Main_Launcher_Render(),
                                                    IMG_Load("Imagens_Golf/Obs.png")),
                       1, 434, 357, 32, 32);
    level_4->Add_Obstacle(level_4->Get_Main_Launcher_Render(),
                       SDL_CreateTextureFromSurface(level_4->Get_Main_Launcher_Render(),
                                                    IMG_Load("Imagens_Golf/Obs1.png")),
                       1, 484, 413, 32, 32);
    level_4->Add_Obstacle(level_4->Get_Main_Launcher_Render(),
                       SDL_CreateTextureFromSurface(level_4->Get_Main_Launcher_Render(),
                                                    IMG_Load("Imagens_Golf/Obs.png")),
                       0, 484, 307, 32, 32);

    level_4->Set_Time(2);
    level_4->Set_Remaining_Moves(15);
    level_4->Set_Timer();

    levels.push_back(std::move(level_4));
    return levels;
}


int main(int argc, char *argv[]) {
    int cursor_x_init, cursor_x_final, cursor_y_init, cursor_y_final;
    bool aux_bool = true;
    SDL_Event event;


    for (auto const &l: initialize_levels()) {
        l->Render();
        while (l->Get_Run()) {

            l->UpdateTimer();
            //Inicialização Padrão de Evento de Tela
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    //Confere caso de fechamento de Janela
                    case SDL_QUIT:
                        IMG_Quit();
                        SDL_Quit();
                        break;
                }

                //Essa pr�xima etapa consiste em verificar quando o jogador aperta a tela arrasta o mouse e solta, esse arrastar é feito a partir da diferen�a entre as posições do cursor
                //quando o jogador aperta e solta



                //Verifica se o Evento de Mouse -> ser apertado ocorreu
                if (SDL_MOUSEBUTTONDOWN == event.type) {
                    //Verifica se a parte do Mouse apertada foi o bot�o esquerdo
                    if (SDL_BUTTON_LEFT == event.button.button) {
                        //Função relacionada com os inputs de dispositivos
                        SDL_PumpEvents();
                        //Função que atribui ao valor associado ao endereço, a posição x e a posição y do cursor
                        SDL_GetMouseState(&cursor_x_init, &cursor_y_init);
                    }
                }
                //Verifica se o Evento de Mouse -> ser soltado ocorreu
                if (SDL_MOUSEBUTTONUP == event.type) {
                    //Verifica se a parte do Mouse soltada foi o bot�o esquerdo
                    if (SDL_BUTTON_LEFT == event.button.button) {
                        SDL_GetMouseState(&cursor_x_final, &cursor_y_final);
                        l->UpdateTimer();
                        l->Mover(cursor_x_init - cursor_x_final, cursor_y_init - cursor_y_final, l->Get_pRun());
                    }

                }

            }

            if (l->Get_Stop()) {
                SDL_DestroyWindow(l->Get_Launcher()->Get_Screen().Get_Window());
                IMG_Quit();
                SDL_Quit();
                return EXIT_SUCCESS;
            }
        }
    }

    IMG_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;

}
