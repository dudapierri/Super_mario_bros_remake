#ifndef FUNCOESJOGOMARIO_H
#define FUNCOESJOGOMARIO_H
    #include <iostream>
    #define SDL_MAIN_HANDLED
    #include <SDL.h>
    #include <vector>
    #include <algorithm>
    #include <SDL_mixer.h>
    #include "structsJogoMario.h"

    using namespace std;

    vector <Obstaculo> iniciaObstaculo();
    void gravidade(SDL_Rect mario, vector <Obstaculo> obstaculos ,int& fase_pulo, int &mapax, float &mapay);
    void verificaColisao(int& mapax, SDL_Rect mario, vector <Obstaculo> &obstaculos ,int& fase_pulo,Mix_Chunk *moeda, vector <Moeda> &moedas, bool &pulo, float &mapay);
    SDL_Texture* carregaImagem (const char *imagem, SDL_Renderer* renderizador);
    void puloMario(int& fase_pulo , bool& pulo,float &mapay);
    void morteMario (SDL_Renderer* renderizador,int fase_pulo, SDL_Rect origem_mario,  SDL_Rect destino_mario, bool &pulo, float &mapay);
    bool colisoesInimigo (SDL_Rect mario, int &mapax, Inimigo &inimigo,int obsx,SDL_Renderer* renderizador,int fase_pulo, SDL_Rect origem_mario,Mix_Chunk *morte_inimigo, bool &pulo, float &mapay);
    void finalFase(int mapax,SDL_Renderer* renderizador,SDL_Texture* mapa_01,SDL_Rect origem_mapa01,SDL_Rect destino_mapa01,SDL_Rect origem_mario,SDL_Rect destino_mario,vector <SDL_Texture*> mario_andando);


#endif // FUNCOESJOGOMARIO_H
