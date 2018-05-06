/*
  OBJ Viewer with Texture

  Author:       Rodrigo Luis de Souza da Silva
  Date:         22/12/2005
  Last Update:  06/12/2017
  Description:  View OBJ files based on the glcWarefrontObject class.
*/


#include <iostream>
#include <string>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <sstream>
#include "glcWavefrontObject.h"
#include "Objeto.h"

#define NUM_OBJECTS 7

using namespace std;
string titulo_janela;

int selecionado = 0;
Objeto objetos[5];
bool wireframe = false;
bool fullscreen = false;

char objectFiles[5][50] =
{
    "../data/obj/snowman.ply",
    "../data/obj/bunny.ply",
    "../data/obj/budda.ply",
    "../data/obj/dragon.ply",
     "../data/obj/cow.ply"
};

typedef struct
{
    //GLMmodel* pmodel = NULL;
    glcWavefrontObject *pmodel = NULL;
} object;

object *objectList;

glcWavefrontObject *objectManager = NULL;

int selected = 0;
int selectedShading = SMOOTH_SHADING;
int selectedRender = USE_MATERIAL;
float dist = 20.0;
int width = 800;
int height = 800;
float rotationX = 0.0, rotationY = 0.0;
int   last_x, last_y;

// Menu
void showMenu()
{
    cout << "OBJECT VIEWER" << endl;
    cout << "-------------\n" << endl;
    cout << "Mouse\n" << endl;
    cout << "* Click to move the object and scroll to zoom in/out." << endl;
    cout << "Keyboard" << endl;
    cout << "* 1 to " << NUM_OBJECTS << " to change objects" << endl;
    cout << "* 's' to change shading mode (FLAT_SHADING or SMOOTH_SHADING)" << endl;
    cout << "* 'r' to change render mode (USE_MATERIAL or USE_COLOR)" << endl;
    cout << "* ESC - Para sair" << endl;
}

//Reshape Func
void reshape( int w, int h)
{
    width = w;
    height = h;
    glViewport(0,0,w,h);
}


void keyboard(unsigned char key, int x, int y)
{
    if(isdigit(key))
    {
        int val = atoi((const char *) &key);
        if(val > 0 && val <= NUM_OBJECTS )
            selected = val-1;
    }

    switch (key)
    {
        case 27 :
            exit(0);
        break;
        case 's':
            selectedShading = (selectedShading == FLAT_SHADING) ? SMOOTH_SHADING : FLAT_SHADING;
        break;
        case 'r':
            selectedRender = (selectedRender == USE_MATERIAL) ? USE_COLOR : USE_MATERIAL;
        break;
        case 'w':
            wireframe = !wireframe;
        break;
        case 'f':
            if(fullscreen){
                fullscreen = false;
                glutReshapeWindow(800,800);
            }
            else{
                fullscreen = true;
                glutFullScreen();
            }
        break;
        case '1':
            selecionado = 0;
        break;
        case '2':
            selecionado = 1;
        break;
        case '3':
            selecionado = 2;
        break;
        case '4':
            selecionado = 3;
        break;
        case '5':
            selecionado = 4;
        break;
    }
    glutPostRedisplay();
}

// Motion callback
void motion(int x, int y )
{
    rotationY += (float) (y - last_y);
    rotationX += (float) (x - last_x);

    last_x = x;
    last_y = y;

    glutPostRedisplay();
}

// Mouse callback
void mouse(int button, int state, int x, int y)
{
    if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
    {
        last_x = x;
        last_y = y;
    }
    if(button == 3) // Scroll up
    {
        if(dist>=5.0)  dist-=1;
    }
    if(button==4)   // Scroll down
    {
        if(dist<=40.0) dist+=1;
    }
}

void display(void)
{
    // Limpar todos os pixels
    glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    // Sistema de Projeção
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0f,(GLfloat)width/(GLfloat)height,0.1f,200.0f);
    gluLookAt (0.0, 0.0, dist, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Sistema de Visualização
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Movimenta o objeto e camera fica parada
    glRotatef( rotationY, 1.0, 0.0, 0.0 );
    glRotatef( rotationX, 0.0, 1.0, 0.0 );

    objetos[selecionado].DesenhaObjeto(wireframe);

    glutSwapBuffers ();
    glutPostRedisplay();
}


void init (void)
{

    // selecionar cor de fundo (preto)
    glClearColor (0.2, 0.2, 0.2, 0.0);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
    glEnable(GL_CULL_FACE);


    //GLfloat light0_position[] = {-3.0f, 3.0f, 10.0f, 1.0f};
    //glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

    GLfloat cor_luz[]  = { 1.0, 1.0, 1.0, 1.0};
   // Posicao da fonte de luz. Ultimo parametro define se a luz sera direcional (0.0) ou tera uma posicional (1.0)
    GLfloat posicao_luz[] = { 50.0, 50.0, 50.0, 1.0};

   // Define parametros da luz
    glLightfv(GL_LIGHT0, GL_AMBIENT, cor_luz);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, cor_luz);
    glLightfv(GL_LIGHT0, GL_SPECULAR, cor_luz);
    glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz);

    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);

    for(int i = 0; i < 5; i++)
        objetos[i].LerPly(objectFiles[i]);

    stringstream ss;
    ss << objetos[selecionado].num_faces;
    titulo_janela = "Numero de faces: " + ss.str() ;
    glutSetWindowTitle(titulo_janela.c_str());

}


int main(int argc, char** argv)
{

    //objectManager->ReadPly("../data/obj/snowman.ply");
    printf("\n\n\n");
    showMenu();
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGB);
    glutInitWindowSize (width, height);
    glutInitWindowPosition (0, 0);
    glutCreateWindow ("Object Viewer");
    init ();
    glutMouseFunc( mouse );
    glutKeyboardFunc(keyboard);
    glutMotionFunc( motion );
    glutReshapeFunc( reshape );
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

