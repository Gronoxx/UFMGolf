#include "Launcher.h"
#include "iostream"
Launcher::Launcher() {
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
    }
    this->screen = SDL_GetWindowSurface(this->Main_Screen.Get_Window());
    this->ren = SDL_CreateRenderer(this->Main_Screen.Get_Window(), -1, SDL_RENDERER_ACCELERATED);
}
SDL_Renderer* Launcher::Get_Render() {
    return this->ren;
}
Screen Launcher::Get_Screen() {
    return this->Main_Screen;
}