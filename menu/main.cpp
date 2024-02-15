#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include "components/Button.hpp"

using namespace std;

bool init();
void kill();
bool loop();
void runLevel1();
void runLevel2();
void actionCredits();
void actionHowToPlay();

// Pointers to our window, renderer, texture, and font
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture *texture, *text;
TTF_Font* font;
string input;
auto buttons = std::vector<std::unique_ptr<Button>>();

int main(int argc, char** args) {

    if ( !init() ) {
        system("pause");
        return 1;
    }

    while ( loop() ) {
        // wait before processing the next frame
        SDL_Delay(10);
    }

    kill();
    return 0;
}

bool loop() {
    SDL_Event e;

    // Clear the window to white
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderClear( renderer );
    for(auto const &b : buttons) b->render(renderer);

    // Event loop
    while ( SDL_PollEvent( &e ) != 0 ) {
        switch (e.type) {
            case SDL_QUIT:
                return false;
            case SDL_TEXTINPUT:
                input += e.text.text;
                break;
            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_BACKSPACE && input.size()) {
                    input.pop_back();
                }
            case SDL_MOUSEBUTTONDOWN:
                if (e.button.button == SDL_BUTTON_LEFT)
                    for (auto const &b: buttons)
                        b->click(e.motion.x, e.motion.y);

                break;
        }
    }

    SDL_Color foreground = { 255, 255, 255 };

    // Update window
    SDL_RenderPresent( renderer );

    return true;
}

bool init() {
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        cout << "Error initializing SDL: " << SDL_GetError() << endl;
        return false;
    }


    // Initialize SDL_ttf
    if ( TTF_Init() < 0 ) {
        cout << "Error intializing SDL_ttf: " << TTF_GetError() << endl;
        return false;
    }

    window = SDL_CreateWindow( "Golf", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 400, SDL_WINDOW_SHOWN );
    if ( !window ) {
        cout << "Error creating window: " << SDL_GetError()  << endl;
        return false;
    }

    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    if ( !renderer ) {
        cout << "Error creating renderer: " << SDL_GetError() << endl;
        return false;
    }

    // Load font
    font = TTF_OpenFont("arial.ttf", 50);
    if ( !font ) {
        cout << "Error loading font: " << TTF_GetError() << endl;
        return false;
    }

    // Start sending SDL_TextInput events
    SDL_StartTextInput();

   buttons.push_back( std::make_unique<Button>("Level 1", 300,60,150,10, font,renderer, runLevel1));
    buttons.push_back( std::make_unique<Button>("Level 2", 300,60,150,80, font,renderer, runLevel2));
    buttons.push_back( std::make_unique<Button>("Credits", 300,60,150,150, font,renderer, actionCredits));
    buttons.push_back( std::make_unique<Button>("How to play", 300,60,150,220, font,renderer, actionHowToPlay));
    buttons.push_back( std::make_unique<Button>("Quit", 300,60,150,290, font,renderer, kill));

    return true;
}
void runLevel1(){
    std::cout << "call run level 1 terminal" << std::endl;
}

void runLevel2(){
    std::cout << "call run level 2 terminal" << std::endl;
}

void actionHowToPlay(){
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "How to play",
                             "O jogo consiste em completar uma fase de golfe, ou seja, deve-se colocar a bola de\n"
                             " golfe no buraco (só temos um de cada em cada fase). Não esqueça de dar a devida atenção aos\n"
                             " obstáculos, eles estão aí para te atrapalhar! Todos os movimentos são feitos a partir do mouse\n"
                             " (botão esquerdo), pressione o botão esquerdo e arraste sobre a tela, quanto mais arrastar \n"
                             "(distância percorrida do cursor) mais forte irá sair a bola, porém não adianta sair arrastando\n"
                             " eternamente, pois há um limite de força, golfe é um jogo de controle não de força bruta lembre-se \n"
                             " disso. A direção da bola é a mesma que você percorrer ao soltar o botão esquerdo do arraste, porém \n"
                             "com direção oposta. Por fim, tome cuidados com as fases que possuem um tempo limite ou número de jogadas\n"
                             " limitadas, o resto você só aprende com a prática, bom jogo! ", window);
}
void actionCredits(){
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Sobre",
                            " Todos nós aprendemos muito com esse trabalho, desde clonar arquivos do Github até detalhes da boa prática de \n"
                            "programação orientada a objetos. Tivemos vários desafios, como modularizar o código da forma adequada, aprender\n"
                            " sobre interface gráfica, conseguir coordenar o esforço em conjunto, pensar de forma coletiva, reconhecer os pontos\n"
                            " fortes e fracos de cada membro, implementar classes mais complexas, utilizar em um código maior conceitos difíceis, \n"
                            "tais como smart pointers, herança, composição, entre outros. Porém, o mais importante foi como conseguimos aprender com\n"
                            "nossos erros e, apesar de estarmos muito longe de um trabalho perfeito, termos conseguido colocar em prática aquilo que \n"
                            "aprendemos durante o semestre e conversar com nossos colegas experiências de aprendizado que deram uma nova visão geral para \n"
                            "cada um.\n\n"
                            "    Estudantes: \n"
                            "    Alícia Marcola Chaves \n"
                            "    Davi Porto Araujo  \n"
                            "    Emanuelle King Amaral \n"
                            "    Gustavo Dias Apolinário ", window);

}

void kill() {
    std::cout <<"here";
    SDL_StopTextInput();

    TTF_CloseFont( font );
    SDL_DestroyTexture( texture );
    texture = NULL;

    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window = NULL;
    renderer = NULL;

    TTF_Quit();
    SDL_Quit();
}

