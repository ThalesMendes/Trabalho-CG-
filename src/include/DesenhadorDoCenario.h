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

        int width  = 1000;
        int height = 500;
};

#endif // DESENHADORDOCENARIO_H
