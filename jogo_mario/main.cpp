#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <vector>
#include <algorithm>
#include <SDL_mixer.h>
#include "funcoesJogoMario.h"
#include "structsJogoMario.h"

using namespace std;

int main(int argc, char* args[])
{
    // ----- funcionamento sdl------------
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0 )
        cout<< SDL_GetError() << endl;
    //-----------------------------------


    int mapax=0;
    float mapay=0;
    bool pulo = false;
    bool gameOver= false;
    bool mostra_menu= true;
    int fase_pulo=0;
    bool esquerda = false;
    bool direita = false;
    int i=0;
    int j=0;
    int a = 0;
    int c=0;
    int tartaruga_posicao = 0;
    int deslocamento_inimigo=0;
    vector <Moeda> moedas;
    SDL_Event evento;



    // ------------- audio --------------
    int frequencia = 22050;
    Uint16 formato = AUDIO_S16SYS;
    int canal= 2;
    int buffer = 4096;
    Mix_OpenAudio(frequencia, formato,canal,buffer);
    Mix_Chunk *trilha_sonora = Mix_LoadWAV("trilha_sonora.wav");
    Mix_Chunk *pulo_mario = Mix_LoadWAV("pulo.wav");
    Mix_Chunk *morte_mario = Mix_LoadWAV("morte_mario.wav");
    Mix_Chunk *morte_inimigo = Mix_LoadWAV("esmagado.wav");
    Mix_Chunk *moeda = Mix_LoadWAV("moeda.wav");
    Mix_Chunk *final_jogo = Mix_LoadWAV("final_jogo.wav");
    Mix_PlayChannel(-1,trilha_sonora,-1);
    //--------------------------------------

    vector <Obstaculo> obstaculos = iniciaObstaculo();



    //------- sprites ------------------------
    SDL_Window* janela = SDL_CreateWindow("Janela Jogo",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,480,0);
    SDL_Renderer* renderizador =  SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture* mapa_01 = carregaImagem("mapa01.bmp",renderizador);
    SDL_Texture* movimento_3 = carregaImagem("mario_movimento_3.bmp",renderizador);
    SDL_Texture* movimento_0 = carregaImagem("mario_movimento_0.bmp",renderizador);
    SDL_Texture* movimento_1 = carregaImagem("mario_movimento_1.bmp",renderizador);
    SDL_Texture* movimento_2 = carregaImagem("mario_movimento_2.bmp",renderizador);
    SDL_Texture* movimento_4 = carregaImagem("mario_movimento_4.bmp",renderizador);
    SDL_Texture* movimento_5 = carregaImagem("mario_movimento_5.bmp",renderizador);
    SDL_Texture* movimento_6 = carregaImagem("mario_movimento_6.bmp",renderizador);
    SDL_Texture* movimento_7 = carregaImagem("mario_movimento_7.bmp",renderizador);
    vector <SDL_Texture*> mario_andando ({movimento_0, movimento_1, movimento_2,movimento_3,movimento_4, movimento_5, movimento_6,movimento_7});
    SDL_Texture* bloco_0 = carregaImagem("bloco_0.bmp", renderizador);
    SDL_Texture* bloco_1 = carregaImagem("bloco_1.bmp", renderizador);
    SDL_Texture* bloco_2 = carregaImagem("bloco_2.bmp", renderizador);
    SDL_Texture* bloco_3 = carregaImagem("bloco_3.bmp", renderizador);
    SDL_Texture* bloco_4= carregaImagem("bloco_usado.bmp",renderizador);
    vector <SDL_Texture*> animacao_bloco_interrogacao ({bloco_0,bloco_1,bloco_2,bloco_3,bloco_4});
    SDL_Texture* inimigo_0 = carregaImagem("inimigo_0.bmp",renderizador);
    SDL_Texture* inimigo_1 = carregaImagem("inimigo_1.bmp",renderizador);
    SDL_Texture* inimigo_2 = carregaImagem("inimigo_2.bmp",renderizador);
    vector <SDL_Texture*> animacao_inimigo ({inimigo_0,inimigo_1, inimigo_2});
    SDL_Texture* tijolo = carregaImagem("tijolo.bmp",renderizador);
    SDL_Texture* game_over= carregaImagem("game_over.bmp",renderizador);
    SDL_Texture* inimigo_morto= carregaImagem("inimigo_morto.bmp",renderizador);
    SDL_Texture* moeda1= carregaImagem("moeda.bmp",renderizador);
    SDL_Texture* logo= carregaImagem("logo.bmp",renderizador);
    SDL_Texture* press= carregaImagem("press.bmp",renderizador);
    //----------------------------------------------------------


    // ----- movimento inimigo-----------
    vector <int> movimento_inimigo;
    for (int var = 0; var < 180; ++var) {
        movimento_inimigo.push_back(var);
    }
    for (int var = 180; var >=0; --var) {
        movimento_inimigo.push_back(var);
    }
    //-----------------------------------



     //------ localização inimigo-----------
     vector <Inimigo> inimigos{
        Inimigo(680,383,32,32),Inimigo(1270,383,32,32),Inimigo(1550,383,32,32),
        Inimigo( 1620,383,32,32),Inimigo(2550,127,32,32),Inimigo(2600,127,32,32),
        Inimigo(2860,383,32,32),Inimigo(3100,383,32,32),Inimigo(3654,383,32,32),
        Inimigo(3700,383,32,32),Inimigo(3700,383,32,32),Inimigo(3800,383,32,32),
        Inimigo(3850,383,32,32),Inimigo(3995,383,32,32),Inimigo(4080,383,32,32),
        Inimigo(5489,383,32,32),Inimigo(5400,383,32,32),Inimigo(3400,383,32,32)
        };
     //---------------------------------------

     while (!gameOver){

         while (SDL_PollEvent(&evento) != 0 )
         {
            if (evento.type == SDL_QUIT)
            {
                 gameOver=true;
            }
            if (evento.type == SDL_KEYUP && evento.key.keysym.sym == SDLK_ESCAPE)
            {
                gameOver=true;
            }
            if (evento.type == SDL_KEYDOWN)
            {
                if (evento.key.keysym.sym == SDLK_RETURN)
                {
                   mostra_menu = false;
                }
                if (evento.key.keysym.sym == SDLK_LEFT)
                {
                    esquerda= true;
                }
                else if (evento.key.keysym.sym == SDLK_RIGHT)
                {
                    direita = true;
                }
                else if (evento.key.keysym.sym == SDLK_SPACE)
                {
                    pulo = true;
                    Mix_PlayChannel(-1,pulo_mario,0);

                }

            }
            else if (evento.type == SDL_KEYUP)
            {
                if (evento.key.keysym.sym == SDLK_LEFT)
                {
                    esquerda= false;
                }
                if (evento.key.keysym.sym == SDLK_RIGHT)
                {
                    direita = false;
                }
            }



         }
         if (esquerda == true)
         {
             if (mapax > 0)
             {
                 mapax = mapax - 3;

             }

         }
         if (direita== true)
         {
             mapax = mapax + 3;


         }

         SDL_RenderClear(renderizador);

         //----- declaração SDL_Rects----------
         SDL_Rect origem_mapa01;
         origem_mapa01.x= mapax;
         origem_mapa01.y=0;
         origem_mapa01.w= 801;
         origem_mapa01.h= 480;

         SDL_Rect destino_mapa01;
         destino_mapa01.x= 0;
         destino_mapa01.y=0;
         destino_mapa01.w = 801;
         destino_mapa01.h = 480;

         SDL_Rect origem_mario;
         origem_mario.x=0;
         origem_mario.y=0;
         origem_mario.w=24;
         origem_mario.h= 32;

         SDL_Rect destino_mario;
         destino_mario.x =66 ;
         destino_mario.y= 383 - mapay;
         destino_mario.w= 24;
         destino_mario.h= 32;

         SDL_Rect origem_interrogacao;
         origem_interrogacao.x= 0;
         origem_interrogacao.y= 0;
         origem_interrogacao.w=32;
         origem_interrogacao.h= 32;

         SDL_Rect origem_inimigo;
         origem_inimigo.x= 0;
         origem_inimigo.y=0;
         origem_inimigo.w=32;
         origem_inimigo.h= 32;

         SDL_Rect origem_tijolo;
         origem_tijolo.x= 0;
         origem_tijolo.y=0;
         origem_tijolo.w=32;
         origem_tijolo.h= 32;

         SDL_Rect destino_tijolo;
         destino_tijolo.x = 641 - mapax;
         destino_tijolo.y= 288;
         destino_tijolo.w= 32;
         destino_tijolo.h= 32;

         SDL_Rect destino_tijolo_1;
         destino_tijolo_1.x = 705 - mapax;
         destino_tijolo_1.y= 288;
         destino_tijolo_1.w= 32;
         destino_tijolo_1.h= 32;

         SDL_Rect destino_tijolo_2;
         destino_tijolo_2.x = 769 - mapax;
         destino_tijolo_2.y= 288;
         destino_tijolo_2.w= 32;
         destino_tijolo_2.h= 32;

         SDL_Rect destino_tijolo_3;
         destino_tijolo_3.x = 2465 - mapax;
         destino_tijolo_3.y= 288;
         destino_tijolo_3.w= 32;
         destino_tijolo_3.h= 32;

         SDL_Rect destino_tijolo_4;
         destino_tijolo_4.x = 2529 - mapax;
         destino_tijolo_4.y= 288;
         destino_tijolo_4.w= 32;
         destino_tijolo_4.h= 32;

         SDL_Rect destino_tijolo_5;
         destino_tijolo_5.x = 2561 - mapax;
         destino_tijolo_5.y= 161;
         destino_tijolo_5.w= 32;
         destino_tijolo_5.h= 32;

         SDL_Rect destino_tijolo_6;
         destino_tijolo_6.x = 2593 - mapax;
         destino_tijolo_6.y= 161;
         destino_tijolo_6.w= 32;
         destino_tijolo_6.h= 32;

         SDL_Rect destino_tijolo_7;
         destino_tijolo_7.x = 2625 - mapax;
         destino_tijolo_7.y= 161;
         destino_tijolo_7.w= 32;
         destino_tijolo_7.h= 32;

         SDL_Rect destino_tijolo_8;
         destino_tijolo_8.x = 2657 - mapax;
         destino_tijolo_8.y= 161;
         destino_tijolo_8.w= 32;
         destino_tijolo_8.h= 32;

         SDL_Rect destino_tijolo_9;
         destino_tijolo_9.x = 2689 - mapax;
         destino_tijolo_9.y= 161;
         destino_tijolo_9.w= 32;
         destino_tijolo_9.h= 32;

         SDL_Rect destino_tijolo_10;
         destino_tijolo_10.x = 2721 - mapax;
         destino_tijolo_10.y= 161;
         destino_tijolo_10.w= 32;
         destino_tijolo_10.h= 32;

         SDL_Rect destino_tijolo_11;
         destino_tijolo_11.x = 2753 - mapax;
         destino_tijolo_11.y= 161;
         destino_tijolo_11.w= 32;
         destino_tijolo_11.h= 32;

         SDL_Rect destino_tijolo_12;
         destino_tijolo_12.x = 2785 - mapax;
         destino_tijolo_12.y= 161;
         destino_tijolo_12.w= 32;
         destino_tijolo_12.h= 32;

         SDL_Rect destino_tijolo_13;
         destino_tijolo_13.x = 2914 - mapax;
         destino_tijolo_13.y= 161;
         destino_tijolo_13.w= 32;
         destino_tijolo_13.h= 32;

         SDL_Rect destino_tijolo_14;
         destino_tijolo_14.x = 2946 - mapax;
         destino_tijolo_14.y= 161;
         destino_tijolo_14.w= 32;
         destino_tijolo_14.h= 32;

         SDL_Rect destino_tijolo_15;
         destino_tijolo_15.x = 2978 - mapax;
         destino_tijolo_15.y= 161;
         destino_tijolo_15.w= 32;
         destino_tijolo_15.h= 32;

         SDL_Rect destino_tijolo_16;
         destino_tijolo_16.x = 3010 - mapax;
         destino_tijolo_16.y= 288;
         destino_tijolo_16.w= 32;
         destino_tijolo_16.h= 32;

         SDL_Rect destino_tijolo_17;
         destino_tijolo_17.x = 3203 - mapax;
         destino_tijolo_17.y= 288;
         destino_tijolo_17.w= 32;
         destino_tijolo_17.h= 32;

         SDL_Rect destino_tijolo_18;
         destino_tijolo_18.x = 3235 - mapax;
         destino_tijolo_18.y= 288;
         destino_tijolo_18.w= 32;
         destino_tijolo_18.h= 32;

         SDL_Rect destino_tijolo_19;
         destino_tijolo_19.x = 3778 - mapax;
         destino_tijolo_19.y= 288;
         destino_tijolo_19.w= 32;
         destino_tijolo_19.h= 32;

         SDL_Rect destino_tijolo_20;
         destino_tijolo_20.x = 3874 - mapax;
         destino_tijolo_20.y= 158;
         destino_tijolo_20.w= 32;
         destino_tijolo_20.h= 32;

         SDL_Rect destino_tijolo_21;
         destino_tijolo_21.x = 3906 - mapax;
         destino_tijolo_21.y= 158;
         destino_tijolo_21.w= 32;
         destino_tijolo_21.h= 32;

         SDL_Rect destino_tijolo_22;
         destino_tijolo_22.x = 3938 - mapax;
         destino_tijolo_22.y= 158;
         destino_tijolo_22.w= 32;
         destino_tijolo_22.h= 32;

         SDL_Rect destino_tijolo_23;
         destino_tijolo_23.x = 4096- mapax;
         destino_tijolo_23.y= 158;
         destino_tijolo_23.w= 32;
         destino_tijolo_23.h= 32;

         SDL_Rect destino_tijolo_24;
         destino_tijolo_24.x = 4194 - mapax;
         destino_tijolo_24.y= 158;
         destino_tijolo_24.w= 32;
         destino_tijolo_24.h= 32;

         SDL_Rect destino_tijolo_25;
         destino_tijolo_25.x = 4129- mapax;
         destino_tijolo_25.y= 286;
         destino_tijolo_25.w= 32;
         destino_tijolo_25.h= 32;

         SDL_Rect destino_tijolo_26;
         destino_tijolo_26.x = 4161 - mapax;
         destino_tijolo_26.y= 286;
         destino_tijolo_26.w= 32;
         destino_tijolo_26.h= 32;

         SDL_Rect destino_tijolo_27;
         destino_tijolo_27.x = 5376- mapax;
         destino_tijolo_27.y= 286;
         destino_tijolo_27.w= 32;
         destino_tijolo_27.h= 32;

         SDL_Rect destino_tijolo_28;
         destino_tijolo_28.x = 5408 - mapax;
         destino_tijolo_28.y= 286;
         destino_tijolo_28.w= 32;
         destino_tijolo_28.h= 32;

         SDL_Rect destino_tijolo_29;
         destino_tijolo_29.x = 5472 - mapax;
         destino_tijolo_29.y= 286;
         destino_tijolo_29.w= 32;
         destino_tijolo_29.h= 32;

         SDL_Rect origem_game_over;
         origem_game_over.x = 0;
         origem_game_over.y= 0;
         origem_game_over.w= 256;
         origem_game_over.h= 256;

         SDL_Rect destino_game_over;
         destino_game_over.x = 251;
         destino_game_over.y= 8;
         destino_game_over.w= 256;
         destino_game_over.h= 256;

         SDL_Rect origem_menu;
         origem_menu.x = 0;
         origem_menu.y= 0;
         origem_menu.w= 350;
         origem_menu.h= 174;

         SDL_Rect destino_menu;
         destino_menu.x = 70;
         destino_menu.y= 60;
         destino_menu.w= 350;
         destino_menu.h= 174;

         SDL_Rect origem_press;
         origem_press.x = 0;
         origem_press.y= 0;
         origem_press.w= 300;
         origem_press.h= 95;

         SDL_Rect destino_press;
         destino_press.x =110;
         destino_press.y= 290;
         destino_press.w= 300;
         destino_press.h= 95;
         //------------------------------


         SDL_RenderCopy(renderizador, mapa_01, &origem_mapa01, &destino_mapa01);

         SDL_RenderCopy(renderizador, mario_andando[((int) esquerda) * 4 + i], &origem_mario, &destino_mario );

         //--- logica blocos de interrogacao--------
         for(Obstaculo obs: obstaculos)
         {

             if (obs.bloco)
             {
                 int apagado = (obs.vida>0) ? j : 4 ;
                 obs.r->x = obs.posicaox - mapax;
                 SDL_RenderCopy(renderizador, animacao_bloco_interrogacao[apagado], &origem_interrogacao, obs.r );

             }

         }
         //-------------------------------------------

        //---- logica inimigos------------------------
         for (Inimigo inimigo: inimigos)
         {

            if (inimigo.vivo)
            {
                inimigo.r->x = inimigo.x + movimento_inimigo[deslocamento_inimigo] - mapax;
                SDL_RenderCopy(renderizador, animacao_inimigo[a], &origem_inimigo, inimigo.r);
            }
            else
            {

                inimigo.r->x = inimigo.x - mapax;
                SDL_RenderCopy(renderizador,inimigo_morto, &origem_inimigo, inimigo.r );
            }
         }
         //----------------------------------------------

         //-------- RenderCopy tijolos-----------------------------
         SDL_RenderCopy(renderizador, tijolo, &origem_tijolo, &destino_tijolo);
         SDL_RenderCopy(renderizador, tijolo, &origem_tijolo, &destino_tijolo_1);
         SDL_RenderCopy(renderizador, tijolo, &origem_tijolo, &destino_tijolo_2);
         SDL_RenderCopy(renderizador, tijolo, &origem_tijolo, &destino_tijolo_3);
         SDL_RenderCopy(renderizador, tijolo, &origem_tijolo, &destino_tijolo_4);
         SDL_RenderCopy(renderizador, tijolo, &origem_tijolo, &destino_tijolo_5);
         SDL_RenderCopy(renderizador, tijolo, &origem_tijolo, &destino_tijolo_6);
         SDL_RenderCopy(renderizador, tijolo, &origem_tijolo, &destino_tijolo_7);
         SDL_RenderCopy(renderizador, tijolo, &origem_tijolo, &destino_tijolo_8);
         SDL_RenderCopy(renderizador, tijolo, &origem_tijolo, &destino_tijolo_9);
         SDL_RenderCopy(renderizador, tijolo, &origem_tijolo, &destino_tijolo_10);
         SDL_RenderCopy(renderizador, tijolo, &origem_tijolo, &destino_tijolo_11);
         SDL_RenderCopy(renderizador, tijolo, &origem_tijolo, &destino_tijolo_12);
         SDL_RenderCopy(renderizador, tijolo, &origem_tijolo, &destino_tijolo_13);
         SDL_RenderCopy(renderizador, tijolo, &origem_tijolo, &destino_tijolo_14);
         SDL_RenderCopy(renderizador, tijolo, &origem_tijolo, &destino_tijolo_15);
         SDL_RenderCopy(renderizador, tijolo, &origem_tijolo, &destino_tijolo_16);
         SDL_RenderCopy(renderizador, tijolo, &origem_tijolo, &destino_tijolo_17);
         SDL_RenderCopy(renderizador, tijolo, &origem_tijolo, &destino_tijolo_18);
         SDL_RenderCopy(renderizador, tijolo, &origem_tijolo, &destino_tijolo_19);
         SDL_RenderCopy(renderizador, tijolo, &origem_tijolo, &destino_tijolo_20);
         SDL_RenderCopy(renderizador, tijolo, &origem_tijolo, &destino_tijolo_21);
         SDL_RenderCopy(renderizador, tijolo, &origem_tijolo, &destino_tijolo_22);
         SDL_RenderCopy(renderizador, tijolo, &origem_tijolo, &destino_tijolo_23);
         SDL_RenderCopy(renderizador, tijolo, &origem_tijolo, &destino_tijolo_24);
         SDL_RenderCopy(renderizador, tijolo, &origem_tijolo, &destino_tijolo_25);
         SDL_RenderCopy(renderizador, tijolo, &origem_tijolo, &destino_tijolo_26);
         SDL_RenderCopy(renderizador, tijolo, &origem_tijolo, &destino_tijolo_27);
         SDL_RenderCopy(renderizador, tijolo, &origem_tijolo, &destino_tijolo_28);
         SDL_RenderCopy(renderizador, tijolo, &origem_tijolo, &destino_tijolo_29);
         //--------------------------------------------------------------------

        verificaColisao(mapax,destino_mario, obstaculos, fase_pulo,moeda,moedas,pulo,mapay);

        //----logica moedas------------------------
        for(Moeda &m: moedas){
            if(m.i == m.deslocamento.size())
                continue;
            m.r->x = m.x - mapax;
            m.r->y = m.y - m.deslocamento[m.i];
            SDL_RenderCopy(renderizador, moeda1, &origem_interrogacao, m.r );
            m.i++;
        }
        //--------------------------------------------

         puloMario(fase_pulo,pulo,mapay);

         gravidade(destino_mario, obstaculos, fase_pulo,mapax,mapay);

         //----------logica morte mario buraco -----------------------
         if (mapay < -100)
         {
             morteMario(renderizador,fase_pulo,origem_mario,destino_mario,pulo,mapay);
             Mix_CloseAudio();
             Mix_OpenAudio(frequencia, formato,canal,buffer);
             Mix_PlayChannel(-1,morte_mario,0);
             SDL_RenderCopy(renderizador,game_over, &origem_game_over, &destino_game_over );
             SDL_RenderPresent(renderizador);
             SDL_Delay(5000);
             gameOver=true;
         }
         //-----------------------------------------------------


         //----------logica movimentacao inimigo-----------------------------
         bool m1= false;

         for (Inimigo& inimigo: inimigos) {

             if(inimigo.vivo){
                 m1 = m1 or   colisoesInimigo (destino_mario,mapax,inimigo,inimigo.x + movimento_inimigo[deslocamento_inimigo],renderizador, fase_pulo,origem_mario, morte_inimigo,pulo,mapay);

             }


          }
          //-------------------------------------------------------

         //--------logica morte mario inimigo-------------------
         if (m1)
         {
            Mix_CloseAudio();
            Mix_OpenAudio(frequencia, formato,canal,buffer);
            Mix_PlayChannel(-1,morte_mario,0);
            SDL_RenderCopy(renderizador,game_over, &origem_game_over, &destino_game_over );
            SDL_RenderPresent(renderizador);
            SDL_Delay(5000);
            gameOver=true;

         }
         //---------------------------------------------------------------

         // ----- logica final jogo ---------------------
         if (mapax+ 66 >= 6349) {
             Mix_CloseAudio();
             Mix_OpenAudio(frequencia,formato,canal,buffer);
             Mix_PlayChannel(-1,final_jogo,1);
             finalFase(mapax,renderizador, mapa_01,origem_mapa01, destino_mapa01, origem_mario, destino_mario, mario_andando);
             gameOver=true;
         }
         //-----------------------------------------------

         //----logica menu--------------------
         if (mostra_menu)
         {
             SDL_RenderCopy(renderizador, logo, &origem_menu, &destino_menu );
              SDL_RenderCopy(renderizador, press, &origem_press, &destino_press );

         }
         //--------------------------------------

         SDL_RenderPresent(renderizador);

         SDL_Delay(1000/30);

         //--- incrementos----------
         if (direita || esquerda)
                i++;




         if (!direita && !esquerda)
                i=0;

         if (i>=3)
            i=0;

         j++;
         if (j>=4)
             j=0;
         a++;
         if (a>=3)
             a=0;
        if (pulo)
            c++;


        deslocamento_inimigo++;
        if (deslocamento_inimigo >=360)
            deslocamento_inimigo=0;

        tartaruga_posicao++;
        if (tartaruga_posicao>=3)
            tartaruga_posicao= 0 ;
        //------------------------

    }
    Mix_CloseAudio();
    SDL_DestroyWindow(janela);
    SDL_Quit();
    return 0;
}
