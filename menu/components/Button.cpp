//
// Created by davi on 11/29/22.
//

#include "Button.hpp"
#include <memory>
#include <utility>


Button::Button(std::string label, int width, int height, int x, int y, TTF_Font *font, SDL_Renderer *render,
               std::function<const void()> action) {
    this->rect = std::make_unique<SDL_Rect>();
    this->rect->w = width;
    this->rect->h = height;
    this->rect->x = x;
    this->rect->y = y;

    SDL_Surface *text_surf = TTF_RenderText_Solid(font, label.c_str(), {0, 0, 0, 255});
    this->label = SDL_CreateTextureFromSurface(render, text_surf);

    this->labelRect = std::make_unique<SDL_Rect>();
    this->labelRect->w = text_surf->w;
    this->labelRect->h = text_surf->h;
    this->labelRect->x = x + 10;
    this->labelRect->y = y;

    this->action = std::move(action);


}

Button::~Button() {
    SDL_DestroyTexture(this->label);
}

void Button::render(SDL_Renderer *render) {
    SDL_SetRenderDrawColor(render, 180, 180, 180, 180);
    SDL_RenderFillRect(render, this->rect.get());
    SDL_RenderCopy(render, this->label, NULL, this->labelRect.get());
}

void Button::click(int x, int y) {
    if (x > this->rect->x && x < this->rect->x + this->rect->w
        && y > this->rect->y && y < this->rect->y + this->rect->h){
        this->action();
    }
}

