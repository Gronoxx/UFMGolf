#pragma once

#include <iostream>
#include <SDL_image.h>
#include <SDL.h>
#include "Screen.h"
#include "Ball.h"
#include "Launcher.h"
#include "Hole.h"
#include "Background.h"
#include "Obstacle.h"
#include "vector"
#include "memory"
#include "Timer.h"

class Level {
private:
    double Time{};
    int Remaining_Moves{};
    double pos_ball_init_x{}, pos_ball_init_y{}, pos_hole_init_x{}, pos_hole_init_y{};
    bool run = true;
    bool stop = false;
    bool *prun = &run;
    float itime = 0.0f;
    int frames = 0;
    int current = 0;
    std::shared_ptr<Launcher> l;
    std::unique_ptr<std::vector<std::shared_ptr<Obstacle>>> obstacles;
    std::unique_ptr<Ball> ball;
    std::unique_ptr<Hole> hole;
    std::unique_ptr<Background> BG;
    EngineUtils::Timer *timer = nullptr;
public:
    Level();

    explicit Level(std::shared_ptr<Launcher> &l);

    void Render();

    void Mover(double Var_x, double Var_y, bool *run);

    void Add_Obstacle(SDL_Renderer *ren, SDL_Texture *Obs_Tx, int id, int x, int y, int w, int h);

    void Dim_Moves();

    int Get_Remaining_Moves();

    double Get_Time();

    double Get_pos_ball_init_x();

    double Get_pos_ball_init_y();

    double Get_pos_hole_init_x();

    double Get_pos_hole_init_y();

    std::shared_ptr<Launcher> Get_Launcher();

    void Set_Remaining_Moves(int Rem);

    void Set_Time(double Time);

    void Set_pos_ball_init_x(double x);

    void Set_pos_ball_init_y(double y);

    void Set_pos_hole_init_x(double x);

    void Set_pos_hole_init_y(double y);

    SDL_Renderer *Get_Main_Launcher_Render();

    bool Get_Run();

    void Set_Run(bool b);

    bool Get_Stop();

    void Set_Stop(bool s);

    void Set_Ball(std::unique_ptr<Ball> b);

    void Set_BackGround(std::unique_ptr<Background> b);

    void Set_Hole(std::unique_ptr<Hole> b);

    void Set_Timer();

    bool *Get_pRun();

    void setLaucher(const std::shared_ptr<Launcher>& la);

    void UpdateTimer();
};
