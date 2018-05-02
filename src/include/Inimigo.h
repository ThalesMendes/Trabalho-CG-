#ifndef INIMIGO_H
#define INIMIGO_H
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

class Inimigo
{
    public:
        float x;
        float y;
        bool movel;
        float maxMovimentoX;
        float movimento = 0;
        int sinal = 1;
        int pontos = 60;
        bool vivo;
        int tipo;
        float raio;
        float ladoA;
        float ladoB;
        bool houveColisao = false;

        Inimigo();
        ~Inimigo();

        Inimigo* instanciaInimigo();
        void desenhaInimigo();
        void checaVida(float yAviao, Inimigo inimigos[]);
        void verificaVida(float yAviao);
};

#endif // INIMIGO_H
