#include "DesenhadorDoCenario.h"
#define ESQUERDA TRUE
#define DIREITA FALSE
#define NUM_VERTICES 149
#include <math.h>


DesenhadorDoCenario::DesenhadorDoCenario()
{
    //ctor
}

DesenhadorDoCenario::~DesenhadorDoCenario()
{
    //dtor
}

void DesenhadorDoCenario::desenhaCenario(){

    ///Esse é o verde para o cenario
    glColor3f(0.35, 0.8, 0);

    glBegin(GL_POLYGON);
        glVertex2d(0, 24200);
        glVertex2d(1000, 24200);
        glVertex2d(1000, 25000);
        glVertex2d(0, 25000);
    glEnd();

    //Partes direita e esquerda do obstaculo no cenario dos 2:11 do video
    criaObstaculo4(DIREITA);
    criaObstaculo4(ESQUERDA);

    //Partes direita e esquerda do obstaculo no cenario dos 1:57 do video
    criaObstaculo3(DIREITA);
    criaObstaculo3(ESQUERDA);

    //Partes direita e esquerda do obstaculo no cenario dos 1:30 do video
    criaObstaculo2(DIREITA);
    criaObstaculo2(ESQUERDA);

    //Partes direita e esquerda do obstaculo no cenario dos 1:25 do video
    criaObstaculo1(DIREITA, 12300);
    criaObstaculo1(ESQUERDA, 12300);

    //Partes direita e esquerda do obstaculo no cenario dos 0:45 do video
    criaObstaculo1(DIREITA, 5100);
    criaObstaculo1(ESQUERDA, 5100);

    //Obstaculo aos 0:37 do video
    glBegin(GL_POLYGON);
        glVertex3d(width/2 -100, 3650,0);
        glVertex3d(width/2 +100, 3650,0);
        glVertex3d(width/2 +100, 4150,0);
        glVertex3d(width/2 -100, 4150,0);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex3d(width/2 -100, 3650,50);
        glVertex3d(width/2 +100, 3650,50);
        glVertex3d(width/2 +100, 4150,50);
        glVertex3d(width/2 -100, 4150,50);
    glEnd();


    glBegin(GL_POLYGON);
        glVertex3d(width/2 -100, 3650,0);
        glVertex3d(width/2 +100, 3650,0);
        glVertex3d(width/2 -100, 3650,50);
        glVertex3d(width/2 +100, 3650,50);
        glVertex3d(width/2 +100, 4150,0);
        glVertex3d(width/2 -100, 4150,0);
        glVertex3d(width/2 +100, 4150,50);
        glVertex3d(width/2 -100, 4150,50);
    glEnd();


    glBegin(GL_POLYGON);
        glVertex3d(width/2 +100, 3650,0);
        glVertex3d(width/2 +100, 3650,50);
        glVertex3d(width/2 +100, 4150,0);
        glVertex3d(width/2 +100, 4150,50);

    glEnd();
}

//Desenha os obstaculos aos 0'45'' e 1'25''
//Entrada: bool esquerda: indica se deve ser densenhado a parte da esquerda ou da direita do obstaculo
//         verticeInicial: coordenada Y do primeiro vertice do obstaculo, serve como base para os proximos vertices
//Saida: nenhuma
void DesenhadorDoCenario::criaObstaculo1(bool esquerda, int verticeInicial){
    int localWidth;

    //se é para desenhar a esquerda, a coordenada X é a constante
    if(esquerda)
        localWidth = 0;
    //se não, devemos mudar o X para o outro lado da tela, para isso fazemos width - X
    else
        localWidth = width;

    glBegin(GL_TRIANGLE_STRIP);
        glVertex2d(abs(localWidth - 500), verticeInicial + 0);  ///1
        glVertex2d(abs(localWidth - 500), verticeInicial + 100);///2
        glVertex2d(abs(localWidth - 300), verticeInicial + 100);///3
        glVertex2d(abs(localWidth - 500), verticeInicial + 450);///4
        glVertex2d(abs(localWidth - 300), verticeInicial + 450);///5
        glVertex2d(abs(localWidth - 500), verticeInicial + 525);///6
        glVertex2d(abs(localWidth - 420), verticeInicial + 525);///7
        glVertex2d(abs(localWidth - 500), verticeInicial + 800);///8
        glVertex2d(abs(localWidth - 420), verticeInicial + 800);///9
        glVertex2d(abs(localWidth - 500), verticeInicial + 850);///10
    glEnd();

      glBegin(GL_TRIANGLE_STRIP);
        glVertex2d(abs(localWidth - 500), verticeInicial + 0);  ///1
        glVertex2d(abs(localWidth - 500), verticeInicial + 100);///2
        glVertex2d(abs(localWidth - 300), verticeInicial + 100);///3
        glVertex2d(abs(localWidth - 500), verticeInicial + 450);///4
        glVertex2d(abs(localWidth - 300), verticeInicial + 450);///5
        glVertex2d(abs(localWidth - 500), verticeInicial + 525);///6
        glVertex2d(abs(localWidth - 420), verticeInicial + 525);///7
        glVertex2d(abs(localWidth - 500), verticeInicial + 800);///8
        glVertex2d(abs(localWidth - 420), verticeInicial + 800);///9
        glVertex2d(abs(localWidth - 500), verticeInicial + 850);///10
    glEnd();

}

//Desenha o obstaculo aos 1'30''
//Entrada: bool esquerda: indica se deve ser densenhado a parte da esquerda ou da direita do obstaculo
//Saida: nenhuma
void DesenhadorDoCenario::criaObstaculo2(bool esquerda){
    int localWidth;
      //se é para desenhar a esquerda, a coordenada X é a constante
    if(esquerda)
        localWidth = 0;
    //se não, devemos mudar o X para o outro lado da tela, para isso fazemos width - X
    else
        localWidth = width;

     float verticesObstaculo[]{
        500, 14100, ///1
        500, 14200, ///2
        350, 14200, ///3
        500, 14450, ///4
        350, 14450, ///5
        320, 14451, ///6
        500, 14450, ///7
        500, 14850, ///8
        320, 14451, ///9
        320, 14850, ///10
        500, 14850, ///11
        500, 14950, ///12
     };



    glBegin(GL_TRIANGLE_STRIP);
        for(int i = 0; i < 12*2; i+=2)
            glVertex3d(fabs(localWidth - verticesObstaculo[i]), verticesObstaculo[i+1], 0);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
        for(int i = 0; i < 12*2; i+=2)
            glVertex3d(fabs(localWidth - verticesObstaculo[i]), verticesObstaculo[i+1], 50);
    glEnd();

     glBegin(GL_TRIANGLE_STRIP);
        for(int i = 0; i < 12*2; i+=2){
            glVertex3d(fabs(localWidth - verticesObstaculo[i]), verticesObstaculo[i+1], 0);
            glVertex3d(fabs(localWidth - verticesObstaculo[i]), verticesObstaculo[i+1], 50);
        }
    glEnd();

}



//Desenha o obstaculo aos 2'00''
//Entrada: bool esquerda: indica se deve ser densenhado a parte da esquerda ou da direita do obstaculo
//Saida: nenhuma

void DesenhadorDoCenario::criaObstaculo3(bool esquerda){
    int localWidth;

   //se é para desenhar a esquerda, a coordenada X é a constante
    if(esquerda)
        localWidth = 0;
    //se não, devemos mudar o X para o outro lado da tela, para isso fazemos width - X
    else
        localWidth = width;

    float verticesObstaculo[]{
        500, 19200, ///1
        500, 19300, ///2
        200, 19300, ///3
        500, 19550, ///4
        200, 19550, ///5
        500, 19600, ///6
        150, 19600, ///7
        500, 20100, ///8
        150, 20100, ///9
        500, 20150, ///10
        300, 20150, ///11
        500, 20250, ///12
        300, 20250, ///13
        500, 20350, ///14
        200, 20350, ///15
        500, 20550, ///16
        200, 20550, ///17
        500, 20650, ///18
        400, 20650, ///19
        500, 21000, ///20
        400, 21000, ///21
        500, 21100, ///22
    };


    glBegin(GL_TRIANGLE_STRIP);
        for(int i = 0; i < 22*2; i+=2)
            glVertex3d(fabs(localWidth - verticesObstaculo[i]), verticesObstaculo[i+1], 0);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
        for(int i = 0; i < 22*2; i+=2)
            glVertex3d(fabs(localWidth - verticesObstaculo[i]), verticesObstaculo[i+1], 50);
    glEnd();

      glBegin(GL_TRIANGLE_STRIP);
        for(int i = 0; i < 22*2; i+=2){
            glVertex3d(fabs(localWidth - verticesObstaculo[i]), verticesObstaculo[i+1], 0);
            glVertex3d(fabs(localWidth - verticesObstaculo[i]), verticesObstaculo[i+1], 50);
        }
    glEnd();
}

//Desenha o obstaculo aos 2'00''
//Entrada: bool esquerda: indica se deve ser densenhado a parte da esquerda ou da direita do obstaculo
//Saida: nenhuma
void DesenhadorDoCenario::criaObstaculo4(bool esquerda){
      int localWidth;

   //se é para desenhar a esquerda, a coordenada X é a constante
    if(esquerda)
        localWidth = 0;
    //se não, devemos mudar o X para o outro lado da tela, para isso fazemos width - X
    else
        localWidth = width;

     float verticesObstaculo[]{
        500, 22700, ///1
        500, 22900, ///2
        150, 22900, ///6
        500, 23500, ///4
        150, 23500, ///5
        500, 23700, ///6
     };

    glBegin(GL_TRIANGLE_STRIP);
        for(int i = 0; i < 6*2; i+=2)
            glVertex3d(fabs(localWidth - verticesObstaculo[i]), verticesObstaculo[i+1] ,0);
    glEnd();



    glBegin(GL_TRIANGLE_STRIP);
        for(int i = 0; i < 6*2; i+=2)
            glVertex3d(fabs(localWidth - verticesObstaculo[i]), verticesObstaculo[i+1], 50);
    glEnd();

      glBegin(GL_TRIANGLE_STRIP);
        for(int i = 0; i < 6*2; i+=2){
            glVertex3d(fabs(localWidth - verticesObstaculo[i]), verticesObstaculo[i+1] ,0);
            glVertex3d(fabs(localWidth - verticesObstaculo[i]), verticesObstaculo[i+1], 50);
        }
    glEnd();
}

