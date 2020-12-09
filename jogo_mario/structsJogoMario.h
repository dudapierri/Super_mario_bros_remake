#ifndef STRUCTSJOGOMARIO_H
#define STRUCTSJOGOMARIO_H

    #include <iostream>
    #define SDL_MAIN_HANDLED
    #include <SDL.h>
    #include <vector>
    #include <algorithm>
    #include <SDL_mixer.h>

    using namespace std;


    struct Moeda
    {
        int x;
        int y;
        int i=0;
        SDL_Rect* r= new SDL_Rect();
        vector <int> deslocamento {0,10,20,10,0};
        Moeda(int px, int py): x(px), y(py)
           {
               r->w= 32;
               r->h=32;
               r->x = px;
               r->y = py;
           }
    };
    struct Obstaculo
    {
        int tamanhox;
        int tamanhoy;
        int posicaox;
        int posicaoy;
        int vida;
        bool bloco;
        SDL_Rect* r = new SDL_Rect();
        Obstaculo (int tx, int ty, int px, int py, bool b= false, int v=0): tamanhox(tx), tamanhoy (ty), posicaox(px), posicaoy(py), vida(v), bloco(b)
        {
            if (b)
            {
                r->x = px;
                r->y = py;
                r->h = ty;
                r->w = tx;

            }

       }
    };

    struct VerificadorDeColisoes
    {
        const int NAO_COLIDIU = 0,
                  COLIDIU_CIMA = 1,
                  COLIDIU_DIREITA = 2,
                  COLIDIU_BAIXO = 3,
                  COLIDIU_ESQUERDA = 4;

        int obterOrigemColisao(int y1, int x1, int h1, int w1, int y2, int x2, int h2, int w2)
        {
            bool colidiuDireita = checarSeColidiuDireita(x1,w1,x2,w2),
                 colidiuEsquerda = checarSeColidiuEsquerda(x1, w1, x2),
                 colidiuBaixo = checarSeColidiuBaixo(y1,h1,y2,h2),
                 colidiuCima = checarSeColidiuCima(y1, h1, y2),
                 estaEntreX = checarSeEstaEntreX(x1,w1,x2,w2),
                 estaEntreY = checarSeEstaEntreY(y1,h1,y2,h2);

            if (colidiuCima && (colidiuEsquerda || estaEntreX || colidiuDireita))
                return COLIDIU_CIMA;
            if (colidiuDireita && estaEntreY && !(colidiuCima || colidiuBaixo))
                return COLIDIU_DIREITA;
            if (colidiuEsquerda && estaEntreY  && !(colidiuCima || colidiuBaixo))
                return COLIDIU_ESQUERDA;
            if (colidiuBaixo && (colidiuEsquerda || estaEntreX || colidiuDireita))
                return COLIDIU_BAIXO;

            return NAO_COLIDIU;
        }

        bool checarSeColidiuCima(int y1,int h1,int y2)
        {
            return (y1 < y2 && y1 + h1 > y2);
        }
        bool checarSeColidiuDireita(int x1, int w1, int x2,int w2)
        {
            x2 -= 66;
            return (x1 <= x2 + w2 && x1 + w1 >= x2 + w2);
        }
        bool checarSeColidiuBaixo(int y1,int h1,int y2,int h2)
        {
             return (y1 < y2 + h2 && y1 + h1 > y2 + h2);
        }
        bool checarSeColidiuEsquerda( int x1, int w1, int x2)
        {
            x2 -= 66;
            return (x1 + w1 > x2 && x1 < x2);
        }
        bool checarSeEstaEntreX(int x1, int w1, int x2,int w2)
        {
            x2 -= 66;
            return (x1 >= x2 && x1 + w1 <= x2 + w2);
        }
        bool checarSeEstaEntreY(int y1, int h1,int y2, int h2)
        {
            return (y1 >= y2 && y1 <= y2 + h2) || (y1 + h1 >= y2 && y1 + h1 <= y2 + h2);
        }
    };

    struct Inimigo
    {
        bool vivo= true;
        int x;
        SDL_Rect* r= new SDL_Rect();
        Inimigo (int x, int y, int h, int w)
        {
            this->x = x;
            r->x = x;
            r->y = y;
            r->h = h;
            r->w = w;
        }
    };





#endif // STRUCTSJOGOMARIO_H
