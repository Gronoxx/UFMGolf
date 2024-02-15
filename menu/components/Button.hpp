//
// Created by davi on 11/29/22.
//

#ifndef UNTITLED1_BUTTON_HPP
#define UNTITLED1_BUTTON_HPP

#include <iostream>
#include <memory>
#include <utility>
#include <SDL.h>
#include <SDL_ttf.h>
#include <functional>
class Button {
public:
    Button(std::string label, int width, int height, int x, int y, TTF_Font *font, SDL_Renderer *render,
           std::function<const void()>);

    void render(SDL_Renderer *render);

    virtual ~Button();

    void click(int x, int y);

private:
    SDL_Texture *label;
    std::unique_ptr<SDL_Rect> rect, labelRect;
    std::function<const void()> action;

};


#endif //UNTITLED1_BUTTON_HPP
