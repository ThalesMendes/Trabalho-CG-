#ifndef DESENHADORDOCENARIO_H
#define DESENHADORDOCENARIO_H
#include <GL/glut.h>

class DesenhadorDoCenario
{
    public:
        DesenhadorDoCenario();
        ~DesenhadorDoCenario();
        void desenhaCenario();
        void criaObstaculo1(bool esquerda, int verticeInicial);
        void criaObstaculo2(bool esquerda);
        void criaObstaculo3(bool esquerda);
        void criaObstaculo4(bool esquerda);
        bool ChecaColisaoIlhas(float pos_x_aviao, float pos_x_aviao_direita, float pos_y_aviao);
        int width  = 1000;
        int height = 500;
        bool triPoint(float x1, float y1, float x2, float y2, float x3, float y3, float px, float py);
};

#endif // DESENHADORDOCENARIO_H
