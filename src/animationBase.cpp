//tiros: https://unpolishedcreations.com/2014/09/14/projectiles-bullets-using-openglglut/
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <ctime>
#include <math.h>
#include <stdarg.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <Inimigo.h>
#include "DesenhadorDoCenario.h"
#include "Objeto.h"
#define ALTURA_CHAO 100
#define ESQUERDA TRUE
#define DIREITA FALSE
#define HELICOPTERO 1 //esfera
#define SUBMARINO 2   //retangulo
#define AVIAO 3       //quadradp
#define COMBUSTIVEL 4
#define PONTE 5
#define RAIO_TIRO 5
#define NUM_INIMIGOS 124


Objeto aviao;
int offset_x_2D = 0;
int offset_y_2D = 0;
int arruma_posX_2D = 0;
bool projecao3D = true;
bool estava3D = true;
int MAX_TIROS ;

float longe = 2500;
// Globals
int width  = 1000;
int height = 500;
int teste=0;
float yAviao = 0;

float objectPosX = width/2;
float objectPosY = height/2;

std::vector<int> rankPontuacao(10);

float posX = 0;
float moveX = 0;

int podeAbastecer = 0;
int podeAtirar = 0;

int combustivel = 100;
int vidas = 3;
int pontos = 0;

bool jogoPausado = false;
bool fullscreen = false;
bool atirar = false;
bool mostraPontos = false;
bool jogoIniciado = false;
bool fimDoJogo = false;
bool salvaPontosNoFimDoJogo = true;

float checkpoint = 0;

Inimigo inimigo;
Inimigo *inimigos;
DesenhadorDoCenario desenhadorDoCenario;

using namespace std;

class Tiro {
    public:
        float x;
        float y;
        bool ativo;

    Tiro(){
        this->x = 0;
        this->y = 0;
        this->ativo = false;
    }
};


Tiro tiros[25];

float vetorVerticesEsquerda[] =
{
    350, 100,  ///1
    0,   100,  ///2
    350, 200,  ///3
    0,   200,  ///4
    350, 300,  ///5
    0,   300,  ///6
    200, 350,  ///7
    0,   500,  ///8
    200, 500,  ///9
    0,   2000, ///10
    200, 2000, ///11
    350, 2100, ///12
    350, 2300, ///13
    0,   2000, ///14
    0,   2500, ///15
    350, 2300, ///16,
    350, 2450, ///17
    200, 2500, ///18
    0,   2500, ///19
    200, 2750, ///20
    0,   2750, ///21
    150, 2780, ///22
    0,   2780, ///23
    150, 2900, ///24
    0,   2900, ///25
    200, 2930, ///26
    0,   2930, ///27
    200, 3150, ///28
    0,   3150, ///29
    100, 3200, ///30
    0,   3200, ///31
    100, 3500, ///32
    0,   3500, ///33
    50,  3550, ///34
    0,   3550, ///35
    50,  4350, ///36
    0,   4350, ///37
    200, 4400, ///38
    0,   4400, ///39
    200, 4700, ///40
    0,   4700, ///41
    100, 4750, ///42
    0,   4750, ///43
    100, 5000, ///44
    0,   5000, ///45
    50,  5050, ///46
    0,   5050, ///47
    50,  6000, ///48
    0,   6000, ///49
    100, 6050, ///50
    0,   6050, ///51
    100, 6500, ///52
    0,   6500, ///53
    80,  6500, ///54
    80,  6800, ///55
    0,   6500, ///56
    0,   6800, ///57
    80,  6800, ///58 eles foram para resetar pro posicionamento normal
    0,   6800, ///59
    350, 6900, ///60
    0,   6900, ///61
    350, 7300, ///62
    0,   7300, ///63
    200, 7400, ///64
    0,   7400, ///65
    200, 9000, ///66
    0,   9000, ///67
    350, 9100, ///68
    0,   9100, ///69
    350, 9500, ///70
    0,   9500, ///71
    200, 9600, ///72
    0,   9600, ///73
    200, 9800, ///74
    0,   9800, ///75
    250, 9900, ///76
    0,   9900, ///77
    250, 10700, ///78
    0,   10700, ///79
    200, 10800, ///80
    0,   10800, ///81
    200, 11300, ///82
    0,   11300, ///83
    180, 11300, ///84
    180, 11700, ///85
    0,   11300, ///86
    0,   11700, ///87
    180, 11700, ///88
    0,   11700, ///89
    160, 11700, ///90
    160, 12100, ///91
    0,   11700, ///92
    0,   12100, ///93
    160, 12100, ///94
    0,   12100, ///95
    50,  12200, ///96
    0,   12200, ///97
    50,  13300, ///98
    0,   13300, ///99
    150, 13400, ///100
    0,   13400, ///101
    150, 14000, ///102
    0,   14000, ///103
    50,  14100, ///104
    0,   14100, ///105
    50,  15100, ///106
    0,   15100, ///107
    350, 15200, ///108
    0,   15200, ///109
    350, 15600, ///110
    0,   15600, ///111
    200, 15700, ///112
    0,   15700, ///113
    200, 18200, ///114
    0,   18200, ///115
    350, 18300, ///116
    0,   18300, ///117
    350, 18700, ///118
    0,   18700, ///119
    100, 18800, ///120
    0,   18800, ///121
    100, 19200, ///122
    0,   19200, ///123
    50,  19300, ///124
    0,   19300, ///125
    50,  21200, ///126
    0,   21200, ///127
    200, 21300, ///128
    0,   21300, ///129
    200, 21800, ///130
    0,   21800, ///131
    180, 21800, ///132
    180, 22100, ///133
    0,   21800, ///134
    0,   22100, ///135
    180, 22100, ///136
    0,   22100, ///137
    130, 22200, ///138
    0,   22200, ///139
    130, 22600, ///140
    0,   22600, ///141
    50,  22700, ///142
    0,   22700, ///143
    50,  23700, ///144
    0,   23700, ///145
    350, 23800, ///146
    0,   23800, ///147
    350, 24200, ///148
    0,   24200, ///149
 };

#define NUM_VERTICES 149
float yOrthoMin = 0;
float yOrthoMax = 500;
float velocidadeAviao = 0;
float velocidadeTiro = 10;
float velocidadeInimigo = 0;
float vetorVerticesDireita[NUM_VERTICES*2];

void SetMaterial2(){
   GLfloat objeto_ambient[]   = {0.0,	0.0,	0.0, 1.0f};
   GLfloat objeto_difusa[]    = {0.0,	0.0,	0.0, 1.0f};
   GLfloat objeto_especular[] = {0.7,	0.7,	0.04, 1.0f};
   GLfloat objeto_brilho[]    = { 90.0f };

   // Define os parametros da superficie a ser iluminada
   glMaterialfv(GL_FRONT, GL_AMBIENT, objeto_ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, objeto_difusa);
   glMaterialfv(GL_FRONT, GL_SPECULAR, objeto_especular);
   glMaterialfv(GL_FRONT, GL_SHININESS, objeto_brilho);
}

void CalculaNormal2(Vertice v1, Vertice v2, Vertice v3, Vertice *vn)
{
    Vertice v1_temp, v2_temp;
	double len;

   /* Encontra vetor v1 */
   v1_temp.x = v2.x - v1.x;
   v1_temp.y = v2.y - v1.y;
   v1_temp.z = v2.z - v1.z;

   /* Encontra vetor v2 */
   v2_temp.x = v3.x - v1.x;
   v2_temp.y = v3.y - v1.y;
   v2_temp.z = v3.z - v1.z;

   /* Calculo do produto vetorial de v1 e v2 */
   vn->x = (v1_temp.y * v2_temp.z) - (v1_temp.z * v2_temp.y);
   vn->y = (v1_temp.z * v2_temp.x) - (v1_temp.x * v2_temp.z);
   vn->z = (v1_temp.x * v2_temp.y) - (v1_temp.y * v2_temp.x);

   /* normalizacao de n */
   len = sqrt(pow(vn->x,2) + pow(vn->y,2) + pow(vn->z,2));

	vn->x /= len;
	vn->y /= len;
	vn->z /= len;
}

void perdeVida(){
    for(int i = 0; i < NUM_INIMIGOS; i++){
        inimigos[i].houveColisao = false;
    }
    yAviao = checkpoint;
    posX = 0;
    yOrthoMin = checkpoint;
    yOrthoMax = checkpoint + 500;
    velocidadeAviao = 2;
    combustivel = 100;
    vidas--;
}



void idle() {

    if(!jogoPausado && jogoIniciado){
        posX += moveX;
        yOrthoMin += velocidadeAviao;
        yOrthoMax += velocidadeAviao;
        yAviao += velocidadeAviao;
        teste++;
        for(int i = 0; i < MAX_TIROS; i++){
            if(tiros[i].ativo)
                tiros[i].y += velocidadeTiro;
         }

        if(int(yAviao)%70 <= 1)
            combustivel-=1;
        if(combustivel == 0){
            combustivel = 100;
            perdeVida();
        }

        for(int i = 0; i < NUM_INIMIGOS; i++){
            velocidadeInimigo = 1;
            if(inimigos[i].tipo == AVIAO)
                velocidadeInimigo = 2;
            if(inimigos[i].movel){
                inimigos[i].movimento += velocidadeInimigo * inimigos[i].sinal;

                if(inimigos[i].movimento == inimigos[i].maxMovimentoX )
                    inimigos[i].sinal = -1;

                if(inimigos[i].movimento == -1 * inimigos[i].maxMovimentoX)
                    inimigos[i].sinal = 1;
            }
        }
    }

    GLfloat posicao_luz[] = { 500+(posX/10+arruma_posX_2D), yAviao, 0, 1};
    GLfloat posicao_luz1[] = {1300, yAviao + 1600 , 150, 1};
    GLfloat posicao_luz2[] = {500, yAviao+250, 250, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz);
    glLightfv(GL_LIGHT1, GL_POSITION, posicao_luz1);
    glLightfv(GL_LIGHT2, GL_POSITION, posicao_luz2);
    glutPostRedisplay();

}

void specialKeysPress(int key, int x, int y) {
    switch(key)
    {
    case GLUT_KEY_RIGHT:
        moveX = 2;
        break;
    case GLUT_KEY_LEFT:
        moveX = -2;
        break;
    case GLUT_KEY_UP:
        if(velocidadeAviao < 4)
            velocidadeAviao+=0.5;
        break;
    case GLUT_KEY_DOWN:
        if(velocidadeAviao > 1)
            velocidadeAviao-=0.5;
        break;
    case GLUT_KEY_F11:
        if(!fullscreen){
            glutFullScreen();
            fullscreen = true;
        }
        else{
            glutReshapeWindow(width,height);
            fullscreen = false;
        }
        break;
    case GLUT_KEY_F10:
        projecao3D = !projecao3D;
        estava3D = !estava3D;
    break;

    default:
        break;
    }
    glutPostRedisplay();
}

void specialKeysRelease(int key, int x, int y) {
    switch (key)
    {
    case GLUT_KEY_LEFT :
    case GLUT_KEY_RIGHT :
        moveX = 0;
        break;
    case GLUT_KEY_DOWN:
    case GLUT_KEY_UP:
            velocidadeAviao = 2;
        break;
    }
    glutPostRedisplay();
}

//Essa � a funcao que printa uma string na tela.
//Entrada: coordendas de onde o texto deve ser mostrado, o texto a ser mostrado e a variavel (pontos ou vida)
//Saida: nenhuma
void mostraTexto(int x, int y, int z, char *str, int variavel) {
    glRasterPos3f(x, y, z);
    int tamanho = (int)strlen(str);

    int i;
    for(i = 0; i < tamanho; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
    }

    char buffer[10] = {'\0'};
    sprintf(buffer, "%d", variavel );
    int tamanho2 = (int)strlen(buffer);

    for(i = 0; i < tamanho2; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, buffer[i]);
    }
};

//Essa � como a funcao acima, mas ele nao imprime um valor variavel
//Entrada: coordendas de onde o texto deve ser mostrado e o texto a ser mostrado
//Saida: nenhuma
void mostraTextoSemVariavel(int x, int y, int z, char *str) {
    glRasterPos2f(x, y);
    int tamanho = (int)strlen(str);

    int i;
    for(i = 0; i < tamanho; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
    }

}

//Func�o que salva os pontos no txt. Lemos o txt, ordenamos os valores e se a pontua��o atual for maior que a ultima,
//inserimos no vetor e reescremos o txt
//Entrada: nenhuma
//Saida: vetor escrito no txt
void salvaPontos(){

    int valor = 0;
    ///Leio as pontuacoes que ja existiam no txt e coloco elas no vetor
    std::ifstream leTexto;
    leTexto.open("Pontuacao.txt");
    for(int i=0;i<10;i++){
        valor = 0;
        leTexto >> valor;
        rankPontuacao.at(i) = valor;
    }
    leTexto.close();
    ///Coloco a pontuacao do jogo atual caso ela seja maior q meu ultimo colocado no vetor e ordeno
    if(pontos > rankPontuacao.at(0))
        rankPontuacao.at(0) = pontos;
    std::sort(rankPontuacao.begin(),rankPontuacao.end());

    ///Salvo as 10 primeiras pontuacoes
    std::ofstream escreveTexto;
    escreveTexto.open("Pontuacao.txt");
    for(int i=0;i<10;i++){
        escreveTexto << rankPontuacao.at(i);
        escreveTexto << std::endl;
    }
    escreveTexto.close();

}

void init(void){
    glShadeModel (GL_SMOOTH);
    glClearColor (0.0, 0.0, 0.8, 0.0);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);

    //glEnable(GL_COLOR_MATERIAL);
    //glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);

    GLfloat cor_luz[]  = { 1.0, 1.0, 1.0, 1.0};
    GLfloat cor_luz1[]  = { 0.0, 1.0, 1.0, 0.0};
    GLfloat posicao_luz[] = { 500+(posX/10+arruma_posX_2D), yAviao, 0, 1};
    GLfloat posicao_luz1[] = {1300, yAviao + 1600 , 150, 1};
    GLfloat posicao_luz2[] = {500, yAviao +250 , 250, 1};

    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);


    glLightfv(GL_LIGHT0, GL_AMBIENT, cor_luz);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, cor_luz);
    glLightfv(GL_LIGHT0, GL_SPECULAR, cor_luz);
    glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz);

    glLightfv(GL_LIGHT1, GL_AMBIENT, cor_luz1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, cor_luz1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, cor_luz1);
    glLightfv(GL_LIGHT1, GL_POSITION, posicao_luz1);


    glLightfv(GL_LIGHT2, GL_AMBIENT, cor_luz);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, cor_luz);
    glLightfv(GL_LIGHT2, GL_SPECULAR, cor_luz);
    glLightfv(GL_LIGHT2, GL_POSITION, posicao_luz2);

    //initLight(width, height);
}

//Funcao que desenha tiro
//Entrada: tiro a ser desenhado
//Saida: nenhuma;
void desenhaTiro (Tiro *t) {
    glPushMatrix();
        glColor3f(1, 0 ,0);
        glTranslated(t->x, t->y, 0);
        glutSolidSphere(RAIO_TIRO, 100, 100);
    glPopMatrix();
}

//Funcao que checa quais tiros devem ser desenhados e checa quais tiros devem ser apagados
//Entrada: nenhuma
//Saida: nenhuma
void acionaTiro(){

    for (int i = 0; i < MAX_TIROS; i++) {
        if (tiros[i].ativo) {
            desenhaTiro(&tiros[i]);
        }
    }

    if(atirar){
        for(int i = 0; i < MAX_TIROS; i++){
            if(!tiros[i].ativo  && !jogoPausado ){
                tiros[i].ativo = true;
                tiros[i].x = width/2 + posX;
                tiros[i].y = yAviao + 150;
                break;
            }
        }
        atirar = false;
    }


    for(int i = 0; i < MAX_TIROS; i++){
        if(tiros[i].ativo && tiros[i].y > yOrthoMax && !projecao3D)
            tiros[i].ativo = false;
        if(tiros[i].ativo && tiros[i].y > yAviao + longe-1500 && projecao3D)
           tiros[i].ativo = false;
    }


}

void SetMaterial(){
   GLfloat objeto_ambient[]   = {0.0215, 0.1745, 0.0215, 1.0f};
   GLfloat objeto_difusa[]    = {0.07568, 0.61424, 0.07568, 1.0f};
   GLfloat objeto_especular[] = {0.633,	0.727811,0.633, 1.0f};
   GLfloat objeto_brilho[]    = { 90.0f };

   // Define os parametros da superficie a ser iluminada
   glMaterialfv(GL_FRONT, GL_AMBIENT, objeto_ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, objeto_difusa);
   glMaterialfv(GL_FRONT, GL_SPECULAR, objeto_especular);
   glMaterialfv(GL_FRONT, GL_SHININESS, objeto_brilho);
}

//Funcao que checa se os pontos do tiro est�o dentro de um inimigo
//Entrada: tiro e inimigo a serem checados
//Saida: bool que indica se houve a colisao
bool esferaBateuRetangulo(Inimigo enemy, Tiro *tiro){


    if((tiro->x + RAIO_TIRO  >= enemy.x + enemy.movimento && tiro->x - RAIO_TIRO  <= enemy.x + enemy.ladoA + enemy.movimento) &&
        (tiro->y + RAIO_TIRO >= enemy.y && tiro->y + RAIO_TIRO  <= enemy.y + enemy.ladoB) )
            return true;

    return false;
}

bool esferaBateuBoundingQuad(Inimigo enemy, Tiro *tiro){
    float meio_x = ( enemy.maxX - enemy.minX)/2;
    float meio_y = ( enemy.maxY - enemy.minY)/2;
     if((tiro->x + RAIO_TIRO  >= enemy.x + enemy.movimento - meio_x && tiro->x - RAIO_TIRO  <= enemy.x + meio_x + enemy.movimento) &&
        (tiro->y + RAIO_TIRO >= enemy.y - meio_y && tiro->y + RAIO_TIRO  <= enemy.y + meio_y) )
            return true;

    return false;

}

//Funcao que, para todo o tiro, todo o inimigo, checa se eles colidiram. Se sim, deixamos de desenhar o tiro, o inimigo e
//incrementamos a pontua��o
//Entrada: nenhuma
//Saida: nenhuma
void checaColisaoTiroInimigo(){

    float distancia;

    //Para cada tiro, para cada inimigo, verificamos se houve colis�o
    for(int i = 0; i < NUM_INIMIGOS; i++){
        for(int j =0; j < MAX_TIROS; j++){

            if(tiros[j].ativo && inimigos[i].vivo){
//
                if(inimigos[i].tipo == PONTE){
                    if(esferaBateuRetangulo(inimigos[i], &tiros[j])){
                        tiros[j].ativo = false;
                        inimigos[i].vivo = false;
                        pontos+= inimigos[i].pontos;
                        inimigos[i].houveColisao = true;
                        checkpoint = inimigos[i].y - 100;
                    }
                }

                if(inimigos[i].tipo == COMBUSTIVEL){
                    if(esferaBateuRetangulo(inimigos[i],&tiros[j])){
                        tiros[j].ativo = false;
                        inimigos[i].vivo = false;
                        pontos+=inimigos[i].pontos;
                        inimigos[i].houveColisao = true;
                    }
                }


                 if(inimigos[i].tipo == SUBMARINO || inimigos[i].tipo == AVIAO || inimigos[i].tipo == HELICOPTERO ){
                    if(esferaBateuBoundingQuad(inimigos[i], &tiros[j])){
                        tiros[j].ativo = false;
                        inimigos[i].vivo = false;
                        pontos+= inimigos[i].pontos;
                        inimigos[i].houveColisao = true;
                    }
                 }

            }
        }
    }
}

void checaColisaoCenario(){
    int sim = 0;
    for (int i=0;i<NUM_VERTICES*2;i+=2){
        if(sim%10 == 0){
        cout << "yCENARIO: " << vetorVerticesEsquerda[i+1] << endl;
        cout << "xCENARIO: " << vetorVerticesEsquerda[i] << endl;
        cout << "yAVIAO: " << yAviao << endl;
        cout << "xESQUERDaAVIAO: " << width/2 -120 + posX/(10+arruma_posX_2D) << endl;}
        if(yAviao>=vetorVerticesEsquerda[i+1] && yAviao+200 <= vetorVerticesEsquerda[i+1] && vetorVerticesEsquerda[i] >= width/2 - 120 + posX/(10+arruma_posX_2D)){
            perdeVida();
        }
        sim++;
    }
}

bool triPoint(float x1, float y1, float x2, float y2, float x3, float y3, float px, float py) {

  // get the area of the triangle
  float areaOrig = fabs( (x2-x1)*(y3-y1) - (x3-x1)*(y2-y1) );

  // get the area of 3 triangles made between the point
  // and the corners of the triangle
  float area1 =    fabs( (x1-px)*(y2-py) - (x2-px)*(y1-py) );
  float area2 =    fabs( (x2-px)*(y3-py) - (x3-px)*(y2-py) );
  float area3 =    fabs( (x3-px)*(y1-py) - (x1-px)*(y3-py) );

  // if the sum of the three areas equals the original,
  // we're inside the triangle!
  if (area1 + area2 + area3 == areaOrig) {
    return true;
  }
  return false;
}

//Funcao checa se o triangulo bateu no inimigo retangular
//Entrada: inimigo a ser analisado
//Saida: bool que indica se houve colisao
bool trianguloBateuRetangulo(Inimigo inimigo){

    float xNaveAcima = width/2 + posX;
    float yNaveAcima = 150 + yAviao;

    if( (xNaveAcima >= inimigo.x + inimigo.movimento && xNaveAcima <= inimigo.x + inimigo.ladoA + inimigo.movimento) &&
        (yNaveAcima >= inimigo.y && yNaveAcima <= inimigo.y + inimigo.ladoB) )
            return true;

    float xNaveDireita = width/2 + 20 + posX;
    float yNaveDireita = 110 + yAviao;

    if( (xNaveDireita >= inimigo.x + inimigo.movimento && xNaveDireita <= inimigo.x + inimigo.ladoA + inimigo.movimento) &&
        (yNaveDireita >= inimigo.y && yNaveDireita <= inimigo.y + inimigo.ladoB) )
            return true;

    float xNaveEsquerda = width/2 - 20 + posX;
    float yNaveEsquerda = 110 + yAviao;

    if( (xNaveEsquerda >= inimigo.x + inimigo.movimento && xNaveEsquerda <= inimigo.x + inimigo.ladoA + inimigo.movimento) &&
        (yNaveEsquerda >= inimigo.y && yNaveEsquerda <= inimigo.y + inimigo.ladoB) )
            return true;


    return false;
}

bool trianguloBateuRetangulo2(Inimigo inimigo){

    float outro_offset_2D;
    projecao3D ? outro_offset_2D = 110.0f : outro_offset_2D = 0.0f;
    float xNaveAcima = width/2 + posX;
    float yNaveAcima = 70 + yAviao + outro_offset_2D;

     float meio_x_inimigo = ( inimigo.maxX - inimigo.minX)/2;
    float meio_y_inimigo = ( inimigo.maxY - inimigo.minY)/2;
//
//    if(inimigo.tipo == HELICOPTERO && inimigo.y <= 1000)
//        cout << "pos inimigo: " <<  inimigo.x - meio_x_inimigo << endl;

    if( (xNaveAcima >= inimigo.x - meio_x_inimigo  + inimigo.movimento && xNaveAcima <= inimigo.x + meio_x_inimigo + inimigo.movimento) &&
        (yNaveAcima >= inimigo.y  - meio_y_inimigo && yNaveAcima <= inimigo.y + meio_y_inimigo) )
            return true;

    float xNaveDireita = width/2 + 20 + posX;
    float yNaveDireita = 150 + yAviao;

    //cout << "xNaveDireita " << xNaveDireita << endl;

    if( (xNaveDireita >= inimigo.x + inimigo.movimento - meio_x_inimigo - 20 && xNaveDireita <= inimigo.x + inimigo.movimento + meio_x_inimigo  ) &&
        (yNaveDireita >= inimigo.y - meio_y_inimigo && yNaveDireita <= inimigo.y + meio_y_inimigo) )
            return true;

    float xNaveEsquerda = width/2 - 20 + posX;
    float yNaveEsquerda = 110 + yAviao;

    if( (xNaveEsquerda >= inimigo.x + inimigo.movimento - meio_x_inimigo && xNaveEsquerda <= inimigo.x + meio_x_inimigo + inimigo.movimento) &&
        (yNaveEsquerda >= inimigo.y - meio_y_inimigo && yNaveEsquerda <= inimigo.y + meio_y_inimigo) )
            return true;


    return false;
}

//Funcao checa se o triangulo bateu no inimigo circular
//Entrada: inimigo a ser analisado
//Saida: bool que indica se houve colisao
bool trianguloBateuEsfera(Inimigo inimigo){
    float xNaveAcima = width/2 + posX;
    float yNaveAcima = 150 + yAviao;

    if( (xNaveAcima > inimigo.x - inimigo.raio + inimigo.movimento && xNaveAcima < inimigo.x + inimigo.raio + inimigo.movimento) &&
        (yNaveAcima > inimigo.y - inimigo.raio && xNaveAcima < inimigo.y + inimigo.raio) )
            return true;


    float xNaveDireita = width/2 + 20 + posX;
    float yNaveDireita = 110 + yAviao;

    if( (xNaveDireita > inimigo.x - inimigo.raio + inimigo.movimento && xNaveDireita < inimigo.x + inimigo.raio + inimigo.movimento) &&
        (yNaveDireita > inimigo.y - inimigo.raio && xNaveDireita < inimigo.y + inimigo.raio) )
            return true;


    float xNaveEsquerda = width/2 - 20 + posX;
    float yNaveEsquerda = 110 + yAviao;

    if( (xNaveEsquerda > inimigo.x - inimigo.raio + inimigo.movimento && xNaveEsquerda < inimigo.x + inimigo.raio + inimigo.movimento) &&
        (yNaveEsquerda > inimigo.y - inimigo.raio && xNaveEsquerda < inimigo.y + inimigo.raio) )
            return true;

    return false;
}


bool aviaoBateuBoundingBox(Inimigo enemy){
//    float meio_x_aviao = ((v_max.x-10.9) - (v_min.x-4.5))/2;
    //float meio_y_aviao = ((aviao.v_max.y-0.3) - (aviao.v_min.y-3.8))/2;


    float meio_x_inimigo = ( enemy.maxX - enemy.minX)/2;
    float meio_y_inimigo = ( enemy.maxY - enemy.minY)/2;

//    cout << "pos aviao: x_min " << fabs((aviao.v_min.x-4.5 + posX)) << endl;
//    cout << "pos aviao: x_max " << fabs((aviao.v_max.x-10.9 + posX)) << endl;
//    cout << "pos aviao: y_max " << fabs((aviao.v_max.y-0.3 )) << endl;

//


    if(
       (yAviao + 200 + offset_y_2D >= enemy.y - meio_y_inimigo && yAviao + 200 + offset_y_2D <= enemy.y + meio_y_inimigo)
       &&
        (
         (455 + posX*1.15 + offset_x_2D <= enemy.x + meio_x_inimigo + enemy.movimento && 455 + posX*1.15 +  offset_x_2D >= enemy.x - meio_x_inimigo + enemy.movimento)
       ||
         (545 + posX*1.15 + + offset_x_2D >= enemy.x - meio_x_inimigo + enemy.movimento && 545+posX*1.15 + offset_x_2D  <= enemy.x + meio_x_inimigo + enemy.movimento)
         )
    )
        return true;
    else
        return false;
}

//Funcao que, todo o inimigo, checa se ele colidiu com o avi�o. Se sim, deixamos de desenhar o tiro, o inimigo e
//incrementamos a pontua��o
//Entrada: nenhuma
//Saida: saida
void checaColisaoAviaoInimigo(){

    float distancia;

    for(int i = 0; i < NUM_INIMIGOS; i++){

        if(inimigos[i].tipo == COMBUSTIVEL && inimigos[i].vivo && !jogoPausado){
            if( trianguloBateuRetangulo(inimigos[i]) ){
                podeAbastecer++;
                if(combustivel < 100 && podeAbastecer % 5 == 0 ){
                    combustivel++;
                    podeAbastecer = 0;

                }
            }
        }

        if((inimigos[i].tipo == SUBMARINO || inimigos[i].tipo == AVIAO) && inimigos[i].vivo){
            if(aviaoBateuBoundingBox(inimigos[i])){
                    perdeVida();
            }
        }

        if(inimigos[i].tipo == PONTE && inimigos[i].vivo){
            if(inimigos[i].y <= yAviao + 150)
                perdeVida();
        }
        if(inimigos[i].tipo == HELICOPTERO && inimigos[i].vivo){
            if(trianguloBateuRetangulo2(inimigos[i])){
                perdeVida();
            }
        }
    }
}



//Funcao que desenha todo o jogo e o menu
//Entrada: nenhuma
//Saida: nenhuma
void desenhaJogo2D(){
    glClearColor (0.0, 0.0, 0.8, 0.0);

    if(jogoPausado){
        glColor3f(0, 1, 1);
        mostraTextoSemVariavel(470, yAviao + 250, 0, "Pause");
    }

    SetMaterial2();
    //glColor3f(1, 1, 0);
    ///Combustivel, Vida e Pontos

    char strCombustivel [] = "Combustivel: ";
    mostraTexto(400, yAviao + 60,0, strCombustivel, combustivel);
    char strVidas [] = "Vidas: ";
    mostraTexto(400, yAviao + 40,0, strVidas, vidas);
    char strPontos [] = "Pontos: ";
    mostraTexto(400, yAviao + 20,0, strPontos, pontos);

    SetMaterial();

    ///Esse � o retangulo que indica os pontos e combustivel
    //glColor3f(0.5, 0.5, 0.5); ///Cinza
    glPushMatrix();
        glTranslatef(0, yAviao, 0);
        glBegin(GL_POLYGON);
            glVertex2f(0.0, 0.0);
            glVertex2f(width, 0);
            glVertex2f(width, ALTURA_CHAO);
            glVertex2f(0, ALTURA_CHAO);
        glEnd();
    glPopMatrix();


    desenhadorDoCenario.desenhaCenario();

    ///Aqui s�o feitos todos os vertices do cenario
    //Parte da esquerda
    glBegin(GL_TRIANGLE_STRIP);
    for(int i = 0; i < 2*NUM_VERTICES; i+=2 )
    {
        glVertex3d(vetorVerticesEsquerda[i], vetorVerticesEsquerda[i+1], 0);
    }
    glEnd();


    //Parte da direita
    glBegin(GL_TRIANGLE_STRIP);
    for(int i = 0; i < 2*NUM_VERTICES; i+=2 )
    {
        glVertex3d(vetorVerticesDireita[i], vetorVerticesDireita[i+1], 0);
    }
    glEnd();


    ///TIROS
    acionaTiro();

    ///Esse � o aviao
//    glPushMatrix();
//        glTranslatef(posX, yAviao, 0);
//        glBegin(GL_TRIANGLE_STRIP);
//            glColor3f(1, 1, 0);
//            glVertex2d(width/2 - 20, 110);
//            glVertex2d(width/2 + 20, 110);
//            glVertex2d(width/2, 150);
//        glEnd();
//    glPopMatrix();

    glColor3f(1, 1, 1);

    ///Aqui deixamos vivos apenas os inimigos que estao dentro do ortho com excecao dos combustiveis
    ///que devem ser desenhados a todo momento
    for(int i = 0; i < NUM_INIMIGOS; i++){
        if(inimigos[i].y > yOrthoMin + 100 && inimigos[i].y < yOrthoMax + 100 && !inimigos[i].houveColisao && inimigos[i].tipo != AVIAO){
            inimigos[i].vivo = true;
        }
        else{
            if(inimigos[i].tipo != COMBUSTIVEL){
                inimigos[i].vivo = false;
            }
        }
    }
    ///Aqui Desenhamos os inimigos que estao dentro do ortho atual (estao Vivos)
    for(int i = 0; i < NUM_INIMIGOS; i++){
        if(inimigos[i].tipo != AVIAO)
            inimigos[i].desenhaInimigo();
    }
}





void desenhaJogo3D(){
    glClearColor (0.0, 0.0, 0.8, 0.0);

    if(jogoPausado){
        glColor3f(0, 1, 1);
        mostraTextoSemVariavel(470, yAviao + 250, 0, "Pause");
    }

    SetMaterial2();
    //glColor3f(1, 1, 0);
    ///Combustivel, Vida e Pontos
    char strCombustivel [] = "Combustivel: ";
    mostraTexto(300, yAviao + 1900 ,150, strCombustivel, combustivel);
    char strVidas [] = "Vidas: ";
    mostraTexto(-200, yAviao + 1600,150, strVidas, vidas);
    char strPontos [] = "Pontos: ";
    mostraTexto(1000, yAviao + 1000, 150, strPontos, pontos);

    SetMaterial();
    desenhadorDoCenario.desenhaCenario();


    ///Aqui s�o feitos todos os vertices do cenario
    //Parte da esquerda
    glBegin(GL_TRIANGLE_STRIP);
    for(int i = 0; i < 2*NUM_VERTICES; i+=2 )
    {
        glVertex3d(vetorVerticesEsquerda[i], vetorVerticesEsquerda[i+1], 0);
    }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    for(int i = 0; i < 2*NUM_VERTICES; i+=2 )
    {
        //glNormal3f(0,0,1);
        glVertex3d(vetorVerticesEsquerda[i], vetorVerticesEsquerda[i+1], 100);
    }
    glEnd();


    glBegin(GL_TRIANGLE_STRIP);
    for(int i = 0; i < 2*NUM_VERTICES; i+=2 )
    {
//        Vertice v1, v2, v3;
//        v1.x = vetorVerticesEsquerda[i+0];
//        v1.y = vetorVerticesEsquerda[i+1];
//        v1.z = 100;
//
//        v2.x = vetorVerticesEsquerda[i+2];
//        v2.y = vetorVerticesEsquerda[i+3];
//        v2.z = 100;
//
//        v3.x = vetorVerticesEsquerda[i+4];
//        v3.y = vetorVerticesEsquerda[i+5];
//        v3.z = 100;
        glVertex3d(vetorVerticesEsquerda[i], vetorVerticesEsquerda[i+1], 0);
        glVertex3d(vetorVerticesEsquerda[i], vetorVerticesEsquerda[i+1], 100);

    }
    glEnd();


    //Parte da direita
    glBegin(GL_TRIANGLE_STRIP);
    for(int i = 0; i < 2*NUM_VERTICES; i+=2 )
    {
        glVertex3d(vetorVerticesDireita[i], vetorVerticesDireita[i+1], 0);
    }
    glEnd();


    //Parte da direita
    glBegin(GL_TRIANGLE_STRIP);
    for(int i = 0; i < 2*NUM_VERTICES; i+=2 )
    {
        glVertex3d(vetorVerticesDireita[i], vetorVerticesDireita[i+1], 100);
    }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    for(int i = 0; i < 2*NUM_VERTICES; i+=2 )
    {
        Vertice um;
        glVertex3d(vetorVerticesDireita[i], vetorVerticesDireita[i+1], 0);
        glVertex3d(vetorVerticesDireita[i], vetorVerticesDireita[i+1], 100);

    }
    glEnd();

    ///TIROS
    acionaTiro();

    ///Esse � o aviao

//    glPushMatrix();
//        glTranslatef(posX, yAviao, 0);
//        glBegin(GL_TRIANGLE_STRIP);
//            glColor3f(1, 1, 0);
//            glVertex2d(width/2 - 20, 110);
//            glVertex2d(width/2 + 20, 110);
//            glVertex2d(width/2, 150);
//        glEnd();
//    glPopMatrix();

   // glColor3f(1, 1, 1);

    ///Aqui deixamos vivos apenas os inimigos que estao dentro do ortho com excecao dos combustiveis
    ///que devem ser desenhados a todo momento
    for(int i = 0; i < NUM_INIMIGOS; i++){
        if(inimigos[i].y > yAviao + 100 && inimigos[i].y < yAviao + longe + 100 && !inimigos[i].houveColisao && inimigos[i].tipo != AVIAO){
            inimigos[i].vivo = true;
        }
        else{
            if(inimigos[i].tipo != COMBUSTIVEL){
                inimigos[i].vivo = false;
            }
        }
    }
    ///Aqui Desenhamos os inimigos que estao dentro do ortho atual (estao Vivos)
    for(int i = 0; i < NUM_INIMIGOS; i++){
        if(inimigos[i].tipo != AVIAO)
            inimigos[i].desenhaInimigo();

    }
}

//Funcao que desenha a tela de pontuacao
//Entrada: nenhuma
//Saida: saida
void desenhaGameOver(){

    velocidadeAviao = 0;
    int yTexto = 0;
    glClearColor(0.5, 0.5, 0.5, 1);
    int valor;

    std::ifstream leTexto;
    leTexto.open("Pontuacao.txt");
    for(int i=0;i<10;i++){
        leTexto >> valor;
        rankPontuacao.at(i) = valor;
    }
    leTexto.close();

    mostraTextoSemVariavel(width/2 -60, yAviao + 400, 0, "High Scores:");
    for(int i = 9; i >= 0; i--){
        mostraTexto(width/2 - 20, yAviao + 350 + yTexto , 0, "", rankPontuacao.at(i));
        yTexto -= 30;
    }

}



void keyboard (unsigned char key, int x, int y) {
    switch(key)
    {
    case 27:
        exit(0);
        break;
    case 'p':
        if(!jogoPausado){
            velocidadeAviao = 0;
            jogoPausado = true;
        }
        else{
            velocidadeAviao = 2;
            jogoPausado = false;
        }
        break;
    case 'r':
        for(int i = 0; i < NUM_INIMIGOS; i++)
            inimigos[i].houveColisao = false;
        jogoIniciado = false;
        yAviao = 0;
        posX = 0;
        yOrthoMin = 0;
        yOrthoMax = 500;
        velocidadeAviao = 2;
        combustivel = 100;
        vidas = 3;
        pontos = 0;
        checkpoint = 0;
        projecao3D = true;
        estava3D = true;
        break;
    case '1':
        jogoIniciado = true;
        velocidadeAviao = 2;
        break;
    case '2':
        if(!mostraPontos){
            mostraPontos = true;
            jogoPausado = true;
        }
        else {
            mostraPontos = false;
        }
        break;
    case ' ':
        if(jogoIniciado && podeAtirar % 10 == 0)
            atirar = true;
        podeAtirar++;
        break;
    default:
        break;
    }
}

void keyboardRelease (unsigned char key,int x, int y){
    switch(key){
    case ' ':
        atirar = false;
        podeAtirar = 0;
        break;
    default:
        break;
    }
}

void display() {
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity ();


    if(yAviao + 150 >= 24200 && salvaPontosNoFimDoJogo){

        fimDoJogo = true;
        projecao3D = false;
        salvaPontosNoFimDoJogo = false;
        salvaPontos();
    }

    checaColisaoTiroInimigo();
    checaColisaoAviaoInimigo();
    for(int i = 0; i < NUM_VERTICES*2; i+=2)
        if(triPoint(vetorVerticesEsquerda[i], vetorVerticesEsquerda[i+1],
                    vetorVerticesEsquerda[i+2], vetorVerticesEsquerda[i+3],
                    vetorVerticesEsquerda[i+4], vetorVerticesEsquerda[i+5],
                    455 - offset_x_2D + posX/1.15, yAviao) )
            perdeVida();

    int arrumaTranslateY = 0;
    if(projecao3D){
        arrumaTranslateY = -25;
        arruma_posX_2D = 0;
    }
    else{
        arrumaTranslateY = -15;
        arruma_posX_2D = 4;
    }

    if(!projecao3D){
        offset_x_2D = 30;
        offset_y_2D = -40;
    }
    else{
        offset_x_2D = 0;
        offset_y_2D = 0;
    }
//    glPushMatrix();
//    glTranslated(posX/1.15, yAviao, 0);
//    glBegin(GL_LINE_LOOP);
//        glVertex3f(455 - offset_x_2D, 140 + offset_y_2D, 0);
//        glVertex3f(545 + offset_x_2D, 140 + offset_y_2D, 0);
//        glVertex3f(545 + offset_x_2D, 200 + offset_y_2D, 0);
//        glVertex3f(455 - offset_x_2D, 200 + offset_y_2D, 0);
//    glEnd();
//    glPopMatrix();


    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();

    if(!projecao3D){
        if(!mostraPontos && vidas >= 0){
            glPushMatrix();
                glScalef(0.03, 0.03 ,0.03);
                glTranslatef(posX/(10+arruma_posX_2D), arrumaTranslateY, 0);
                glRotatef(90, 0, 1, 0);
                glRotatef(-30, 0, 0, 1);
                aviao.DesenhaObjeto(false, 2);
            glPopMatrix();
        }

        MAX_TIROS = 10;
        glOrtho(0.0, width, yOrthoMin, yOrthoMax, 30, -30);
        if(vidas > 0 && !fimDoJogo){
            if(mostraPontos){
                desenhaGameOver();
            }
             else{
                if(estava3D)
                    projecao3D = true;
                desenhaJogo2D();
            }
        }
        else{
            if(vidas == 0){
                vidas--;
                salvaPontos();
            }
            desenhaGameOver();
        }
    }
    else{
    if(!mostraPontos && vidas >= 0){
        glPushMatrix();
            glScalef(0.03, 0.03 ,0.03);
            glTranslatef(posX/(10+arruma_posX_2D), arrumaTranslateY, 0);
            glRotatef(90, 0, 1, 0);
            glRotatef(-30, 0, 0, 1);
            aviao.DesenhaObjeto(false, 2);
        glPopMatrix();
    }
        gluPerspective(40.0f,(GLfloat)width/(GLfloat)height, 0.01 ,longe);
        gluLookAt(500, yAviao-170, 250, 500, 500 + yAviao, 0 , 0, 0, 1);
        MAX_TIROS = 15;
        if(vidas > 0 && !fimDoJogo){
            if(mostraPontos){
                projecao3D = false;
                desenhaGameOver();
            }
             else{
                desenhaJogo3D();
            }
        }
        else{
            if(vidas == 0){
                vidas--;
                projecao3D = false;
                salvaPontos();
            }
            desenhaGameOver();
        }
    }

    glutSwapBuffers();
}

void reshape (int w, int h) {
//    width = w;
//    height = h;
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
}

int main(int argc, char** argv) {
    srand(time(NULL));

    inimigos = inimigo.instanciaInimigo();
    inimigo.leInimigo();
    aviao.LerPly("../data/obj/aviao.ply");


    int j;
    for(j=0;j<NUM_VERTICES*2;j++){
        if(j%2 == 0)
            vetorVerticesDireita[j] = width - vetorVerticesEsquerda[j];
        else
            vetorVerticesDireita[j] = vetorVerticesEsquerda[j];
    }

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (width, height);
    glutInitWindowPosition (0, 0);
    glutCreateWindow("River Raid");
    init ();
    glutDisplayFunc(display);
//  glutIgnoreKeyRepeat(1);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardRelease);
    glutSpecialFunc( specialKeysPress );
    glutSpecialUpFunc( specialKeysRelease );

    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
