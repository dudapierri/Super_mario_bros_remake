#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <vector>
#include <algorithm>
#include <SDL_mixer.h>
#include "structsJogoMario.h"
#include "funcoesJogoMario.h"



using namespace std;



  vector <Obstaculo> iniciaObstaculo()
{


    vector <Obstaculo> obstaculos;
        obstaculos.push_back(Obstaculo(32,32,514,286,true,1));
        obstaculos.push_back(Obstaculo(32,32,705,161,true,3));
        obstaculos.push_back(Obstaculo(32,32,673,286,true,1));
        obstaculos.push_back(Obstaculo(32,32,736,286,true,2));
        obstaculos.push_back(Obstaculo(32,32,2497,286,true,1));
        obstaculos.push_back(Obstaculo(32,32,3010,160,true,5));
        obstaculos.push_back(Obstaculo(32,32,3394,287,true,1));
        obstaculos.push_back(Obstaculo(32,32,3489,159,true,2));
        obstaculos.push_back(Obstaculo(32,32,3489,288,true,1));
        obstaculos.push_back(Obstaculo(32,32,3585,288,true,1));
        obstaculos.push_back(Obstaculo(32,32,4130,158,true,1));
        obstaculos.push_back(Obstaculo(32,32,4162,158,true,1));
        obstaculos.push_back(Obstaculo(32,32,5440,288,true,2));
        obstaculos.push_back(Obstaculo(32,32,641,286));
        obstaculos.push_back(Obstaculo(32,32,706,286));
        obstaculos.push_back(Obstaculo(32,32,769,286));
        obstaculos.push_back(Obstaculo(32,32,2465,286));
        obstaculos.push_back(Obstaculo(32,32,2529,286));
        obstaculos.push_back(Obstaculo(32,32,2561,161));
        obstaculos.push_back(Obstaculo(32,32,2593,161));
        obstaculos.push_back(Obstaculo(32,32,2625,161));
        obstaculos.push_back(Obstaculo(32,32,2657,161));
        obstaculos.push_back(Obstaculo(32,32,2689,161));
        obstaculos.push_back(Obstaculo(32,32,2721,161));
        obstaculos.push_back(Obstaculo(32,32,2753,161));
        obstaculos.push_back(Obstaculo(32,32,2785,161));
        obstaculos.push_back(Obstaculo(32,32,2914,161));
        obstaculos.push_back(Obstaculo(32,32,2946,161));
        obstaculos.push_back(Obstaculo(32,32,2978,161));
        obstaculos.push_back(Obstaculo(32,32,3010,288));
        obstaculos.push_back(Obstaculo(32,32,3203,288));
        obstaculos.push_back(Obstaculo(32,32,3235,288));
        obstaculos.push_back(Obstaculo(32,32,3778,288));
        obstaculos.push_back(Obstaculo(32,32,3874,158));
        obstaculos.push_back(Obstaculo(32,32,3906,158));
        obstaculos.push_back(Obstaculo(32,32,3938,158));
        obstaculos.push_back(Obstaculo(32,32,4096,158));
        obstaculos.push_back(Obstaculo(32,32,4194,158));
        obstaculos.push_back(Obstaculo(32,32,4129,286));
        obstaculos.push_back(Obstaculo(32,32,4161,286));
        obstaculos.push_back(Obstaculo(32,32,5376,286));
        obstaculos.push_back(Obstaculo(32,32,5408,286));
        obstaculos.push_back(Obstaculo(32,32,5472,286));
        obstaculos.push_back(Obstaculo(60,65,902,351));
        obstaculos.push_back(Obstaculo(60,96,1221,321));
        obstaculos.push_back(Obstaculo(60,131,1479,286));
        obstaculos.push_back(Obstaculo(60,131,1833,286));
        obstaculos.push_back(Obstaculo(58,65,5221,353));
        obstaculos.push_back(Obstaculo(58,65,5733,353));

        obstaculos.push_back(Obstaculo(33,33,4288,382));
        obstaculos.push_back(Obstaculo(33,64,4321,349));
        obstaculos.push_back(Obstaculo(33,98,4354,316));
        obstaculos.push_back(Obstaculo(33,129,4387,288));
        obstaculos.push_back(Obstaculo(33,129,4479,288));
        obstaculos.push_back(Obstaculo(33,98,4512,316));
        obstaculos.push_back(Obstaculo(33,64,4545,349));
        obstaculos.push_back(Obstaculo(33,33,4578,382));
        obstaculos.push_back(Obstaculo(33,33,4735,382));
        obstaculos.push_back(Obstaculo(33,64,4768,349));
        obstaculos.push_back(Obstaculo(33,98,4801,316));
        obstaculos.push_back(Obstaculo(33,129,4834,288));
        obstaculos.push_back(Obstaculo(33,129,4867,288));
        obstaculos.push_back(Obstaculo(33,129,4961,288));
        obstaculos.push_back(Obstaculo(33,98,4994,316));
        obstaculos.push_back(Obstaculo(33,64,5027,349));
        obstaculos.push_back(Obstaculo(33,64,5027,349));
        obstaculos.push_back(Obstaculo(33,33,5060,382));
        obstaculos.push_back(Obstaculo(33,33,5793,382));
        obstaculos.push_back(Obstaculo(33,33,5825,350));
        obstaculos.push_back(Obstaculo(33,64,5857,318));
        obstaculos.push_back(Obstaculo(33,98,5889,286));
        obstaculos.push_back(Obstaculo(33,129,5921,254));
        obstaculos.push_back(Obstaculo(33,163,5953,222));
        obstaculos.push_back(Obstaculo(33,288,5982,190));
        obstaculos.push_back(Obstaculo(33,258,6014,158));
        obstaculos.push_back(Obstaculo(33,258,6046,158));

    return obstaculos;
}

  void gravidade(SDL_Rect mario, vector <Obstaculo> obstaculos ,int& fase_pulo, int &mapax, float &mapay){
      bool colidiu = false;
      if (fase_pulo > 0 )
      {
          return;
      }
      VerificadorDeColisoes verificador_de_colisoes;
      for (Obstaculo obs : obstaculos)
      {
          int tipo_colisao = verificador_de_colisoes.obterOrigemColisao(mario.y +15,mapax,mario.h,mario.w,obs.posicaoy,obs.posicaox,obs.tamanhoy,obs.tamanhox);

          if (tipo_colisao != 0 )
          {
              colidiu=true;
          }

      }
      bool buraco = false;
      vector <int> esquerda_buraco{2209,2751,4896};
      vector <int> direita_buraco{2272,2848,4958};
      for (int var = 0; var < esquerda_buraco.size(); ++var)
      {
          if (esquerda_buraco[var] < mapax+66 && direita_buraco[var]> mapax+66 + mario.w)
          {
                buraco = true;
                break;

          }

      }
      if (colidiu == false && (mapay >0 or buraco))
      {
           mapay= mapay-10;
           if(mapay <0 && !buraco)
           {
             mapay=0;
           }

      }

  }


  void verificaColisao(int& mapax, SDL_Rect mario, vector <Obstaculo> &obstaculos ,int& fase_pulo,Mix_Chunk *moeda, vector <Moeda> &moedas, bool &pulo, float &mapay)
 {
      VerificadorDeColisoes  verificador_de_colisoes;
      for(Obstaculo &obs : obstaculos)
      {

          int tipo_colisao = verificador_de_colisoes.obterOrigemColisao(mario.y,mapax,mario.h,mario.w,obs.posicaoy,obs.posicaox,obs.tamanhoy,obs.tamanhox);
          if(tipo_colisao ==1)
          {

              mapay = mapay + ((mario.y + mario.h) - obs.posicaoy) + 3;
              fase_pulo =0;
              pulo = false;

          }
          else if( tipo_colisao ==2)
          {
              mapax= mapax +3;
          }
          else if( tipo_colisao ==3)
          {
              if (obs.vida>0)
              {
                    moedas.push_back(Moeda(obs.posicaox,obs.posicaoy - obs.tamanhoy));
                    Mix_PlayChannel(-1,moeda,0);
              }
              obs.vida--;
              fase_pulo=10 ;
              mapay= mapay + (mario.y - (obs.posicaoy + obs.tamanhoy)) +1;


         }
         else if( tipo_colisao ==4)
          {
               mapax = mapax -3;

          }


      }



      }


  SDL_Texture* carregaImagem (const char *imagem, SDL_Renderer* renderizador)
{
    SDL_Surface* surface = SDL_LoadBMP(imagem);
    if (!surface)
        cout<<"erro"<<endl;
    SDL_Texture* textura = SDL_CreateTextureFromSurface(renderizador,surface);
    SDL_FreeSurface(surface);

    return textura;
}


  void puloMario(int& fase_pulo , bool& pulo,float &mapay)
{
    float max_fase_pulo = 20;
    float incrementa_fase_pulo = 30;
    if (pulo == false)
    {
        return;
    }

    if (fase_pulo > max_fase_pulo/ 2 -1)
    {
        mapay = mapay - (abs(max_fase_pulo/2 - fase_pulo -1) / (max_fase_pulo/2)) * incrementa_fase_pulo;

    }
    else{

        mapay = mapay + ((max_fase_pulo/2 - fase_pulo) / (max_fase_pulo/2)) * incrementa_fase_pulo;
    }
    fase_pulo++;
    if (fase_pulo >= max_fase_pulo)
    {
        pulo= false;
        fase_pulo=0;
    }

    if (mapay < 0 )
    {
        mapay= 0;
    }
}


  void morteMario (SDL_Renderer* renderizador,int fase_pulo, SDL_Rect origem_mario,  SDL_Rect destino_mario, bool &pulo, float &mapay)
  {

    SDL_Texture* mario_morte = carregaImagem("mario_morrido.bmp",renderizador);
    pulo= true;
    while (pulo)
    {
        destino_mario.y= 383 - mapay;
        SDL_RenderCopy(renderizador, mario_morte, &origem_mario, &destino_mario );

        SDL_RenderPresent(renderizador);
        puloMario(fase_pulo,pulo,mapay);

        SDL_Delay(100);
        SDL_RenderClear(renderizador);

    }


}


  bool colisoesInimigo (SDL_Rect mario, int &mapax, Inimigo &inimigo,int obsx,SDL_Renderer* renderizador,int fase_pulo, SDL_Rect origem_mario,Mix_Chunk *morte_inimigo, bool &pulo, float &mapay)
  {
    VerificadorDeColisoes verificador_de_colisoes;
    int tipo_colisao = verificador_de_colisoes.obterOrigemColisao(mario.y,mapax,mario.h,mario.w,inimigo.r->y,obsx,inimigo.r->h,inimigo.r->w);
    if(tipo_colisao ==1)
    {
        Mix_PlayChannel(-1,morte_inimigo,0);
        inimigo.vivo = false;
        inimigo.x = obsx;
        return false;

    }
    else if( tipo_colisao ==2)
    {
         morteMario(renderizador,fase_pulo,origem_mario,mario,pulo,mapay);
         return true;

    }

    else if( tipo_colisao ==4)
    {
        morteMario(renderizador,fase_pulo,origem_mario,mario,pulo,mapay);
        return true;

    }

}


  void finalFase(int mapax,SDL_Renderer* renderizador,SDL_Texture* mapa_01,SDL_Rect origem_mapa01,SDL_Rect destino_mapa01,SDL_Rect origem_mario,SDL_Rect destino_mario,vector <SDL_Texture*> mario_andando){
    int i=0;
    while (mapax+ 66 <= 6349 ){
        mapax= mapax +2;
        destino_mario.x = 66 + mapax;
        SDL_RenderCopy(renderizador, mario_andando[ i % 4], &origem_mario, &destino_mario );
        SDL_RenderCopy(renderizador, mapa_01, &origem_mapa01, &destino_mapa01);
        SDL_RenderPresent(renderizador);
        i++;
    }

    SDL_RenderCopy(renderizador, mapa_01, &origem_mapa01, &destino_mapa01);
    SDL_RenderPresent(renderizador);
    SDL_Delay(6000);




}
