/*
  Name:        VectorNormal2D.cpp
  Copyright:   Version 0.1
  Author:      Rodrigo Luis de Souza da Silva
  Date:        11/10/2005
  Description: Compute Normal Vector of a line segment
*/

#ifdef WIN32
#include <windows.h>
#endif
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#define PI 3.1415927

// Classes and Global Variables
class Point
{
   public:
      float x, y;
      Point()
      {
         x = 0.0;
         y = 0.0;
      }
      void move(float nx, float ny)
      {
         x = nx;
         y = ny;
      }
};

int winsizex = 400, winsizey = 400;
Point p[2];

int current = 0;
int inter = 0;
int startMotion = 0;

// Prototypes

void display(void);
void init (void);
void desenhaEixos();
void mouse(int button, int state, int x, int y);
void motion(int mx, int my);
void intersect(Point p1, Point p2, Point p3, Point p4);
void subtract(Point p1, Point p2, Point *X);

void computeNormal(Point p1, Point p2, Point *n);

// Functions

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGB);
   glutInitWindowSize (winsizex, winsizey);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("hello");
   glutMouseFunc( mouse );
   glutMotionFunc(motion);
   init ();
   printf("\nBotao esquerdo move o ponto");
   printf("\nBotao direito troca de ponto");
   glutDisplayFunc(display);
   glutMainLoop();

   return 0;
}

// Mouse callback
void mouse(int button, int state, int x, int y)
{
   if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
      startMotion = 1;
   if ( button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
   {
      startMotion = 0;
      current++;
      if(current == 2)
         current = 0;
   }
}

void desenhaEixos()
{
   glColor3f (0.3, 0.3, 0.3);
   glBegin(GL_LINES);
      glVertex2f (winsizex/2, 0.0);
      glVertex2f (winsizex/2, winsizey);
      glVertex2f (0.0, winsizey/2);
      glVertex2f (winsizex, winsizey/2);
   glEnd();
}

// p2 é o ponto base e p3 é a ponto do segmento no qual se
// quer calcular o angulo
float calculaAngulo(Point p2, Point p3)
{
   float cateto, hipo, y, rad, angle;

   // O ponto p1 é um offset (em x) do ponto p2 (origem)
   Point p1;
   p1.y = p2.y;
   p1.x = p2.x + 10;

   cateto = p3.y - p1.y;
   if(cateto<0) cateto*=-1;
   hipo = sqrt(pow(p2.y - p3.y,2) + pow(p2.x - p3.x,2));
   y = cateto / hipo;
   rad = asin(y);
   angle = rad * 180/PI;

   if(p3.x < p2.x) angle = 90 + (90 - angle);   // Segundo quadrante
   if(p3.y > p2.y) angle = 180 + (180 - angle); // Terceiro e quarto
   return angle;
}

// Desenha seta na origem, translando e rotacionando com parâmetros abaixo
void desenhaSeta(float angle, Point p)
{
   glColor3f(1.0, 1.0, 1.0);
   glPushMatrix();
      glTranslatef(p.x, p.y, 0.0);
      glRotatef(-angle, 0, 0, 1);
      glBegin(GL_TRIANGLES);
         glVertex2f(-5,  5);
         glVertex2f(-5, -5);
         glVertex2f( 5,  0);
      glEnd();
   glPopMatrix();
}

void display(void)
{
   float r = 0.8f;
   Point n;
   // Limpar todos os pixels
	glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

   desenhaEixos();

   glBegin(GL_LINES);
      glColor3f (0.0, 0.0, 1.0);
      glVertex2f(p[0].x, p[0].y);
      glVertex2f(p[1].x, p[1].y);
   glEnd();

   // Desenha extremidade das linhas
   glColor3f (0.0, 0.0, 1.0);
   for(int i = 0; i <= 1; i++)
   {
      glPushMatrix();
         glTranslatef(p[i].x, p[i].y, 0.0);
      glutSolidCube(6.0);
      glPopMatrix();
   }

   // Desenha esfera atual em tamanho menor
   glColor3f (1.0, 1.0, 1.0);
   glPushMatrix();
      glTranslatef(p[current].x, p[current].y, 0.0);
      glutSolidCube(4.0);
   glPopMatrix();

   // Desenha normal
   computeNormal(p[0], p[1], &n);
   // Desenha extremidade das linhas
   glColor3f (1.0, 1.0, 1.0);
   Point PontoMedio, PontoNormal;
   PontoMedio.x = (p[0].x+p[1].x)/2;
   PontoMedio.y = (p[0].y+p[1].y)/2;
   PontoNormal.x = PontoMedio.x + n.x * 100 ;
   PontoNormal.y = PontoMedio.y + n.y * 100 ;
   glBegin(GL_LINES);
      glVertex2f( PontoMedio.x  , PontoMedio.y);
      glVertex2f( PontoNormal.x , PontoNormal.y);
   glEnd();

   desenhaSeta(calculaAngulo(PontoMedio, PontoNormal), PontoNormal);

   glutSwapBuffers ();
   glutPostRedisplay();
}

void motion(int mx, int my)
{
   if(startMotion)
   {
      p[current].x = mx;
      p[current].y = my;
      glutPostRedisplay();
   }
}

void init (void)
{
  // selecionar cor de fundo (preto)
  glClearColor (0.0, 0.0, 0.0, 0.0);
  glLineWidth(2.0);

  // inicializa os pontos
  p[0].y = p[1].y = 200;
  p[0].x = 150; p[1].x = 250;

  // inicializar sistema de viz.
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, winsizex, winsizey, 0.0, -100.0, 100.0);
}

void computeNormal(Point p1, Point p2, Point *n)
{
   Point temp;
   temp.x = p1.x - p2.x;
   temp.y = p1.y - p2.y;

   n->x = -temp.y;
   n->y = temp.x;

   // Normaliza vetor
   float tam = sqrt( pow( (p1.x-p2.x)/2 - n->x,2) +
                     pow( (p1.y-p2.y)/2 - n->y,2) );
   n->x /= tam;
   n->y /= tam;
}


